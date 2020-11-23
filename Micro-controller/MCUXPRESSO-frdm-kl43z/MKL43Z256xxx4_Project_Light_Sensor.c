/**
 * @file    MKL43Z256xxx4_Project_Light_Sensor.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"

/*Declaring delay function*/
void delay(unsigned long msec);

/*Declare global variables*/
volatile int blink = 0;

/*Main code*/
int main(void) {

	/*Init board hardware.*/
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	/*Clock and ports setup*/
//	SIM->SCGC5 |= ((1 << 9) | (1 << 12)); //enable clock to ports A and D
	SIM->SCGC5 |= ((1 << 11) | (1 << 13)); //enable clock to ports C and E
	SIM->SCGC6 |= 0x8000000;	//enable clock to ADC0
	PORTE->PCR[22] &= ~(0x700); //port E pin 22 (ADC0SE3 and light sensor) to be analog .
	PORTE->PCR[31] = 0x100; //port E pin 31 mux=001. Sets LED2 to GPIO with no pull resistor.
	PORTC->PCR[3] |= 0x103; //set up portC pin 3 (SW3) as GPIO with a pull up resistor.
	PTC->PDDR &= ~(0x8); //set data direction of port C pin 3 to input.
	PTE->PDDR |= (1 << 31); // set bit 31 of port E to 1. Sets LED2 (RED) as output.
//	PTE->PDOR |= (1 << 31);	//set LED off.

	/*configure ADC0 */
	ADC0->CFG1 = 0x00000008;	// setting the clock for the ADC. ADICLK=0, MODE=10-BIT CONVERSION, ADLSMP=0, ADIV=00.
	ADC0->SC2 = 0x00000000; //set conversion trigger to be by software (when ther's a write to SC1A).

	/*Interrupt setup*/
	__disable_irq();  //disable global interrupt.
	NVIC_DisableIRQ(PORTC_PORTD_IRQn); //disable portC and portD interrupts.
	PORTC->PCR[3] &= ~(0xF0000); //Set interrupt flag to zero(off).
	PORTC->PCR[3] |= 0xA0000; //Configure interrupt to be raised on the falling edge (That is when pin3 goes form high to low or when SW3 is pushed).
	NVIC_SetPriority(PORTC_PORTD_IRQn, 192); //Set interrupt priority.		NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn); //Clear pending interrupt if any (port C&D ISFR are both set to zero).
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);  //Enable interrupts on portC and portD.
	__enable_irq();  //Enable global interrupt.

	int first = 1;
	int initial = 0;
	int new = 0;
	int x = 0;

	int i = 0;
	while (1) {
		if (blink == 1) {
			for (i = 0; i < x; i++) {
				PTE->PDOR &= ~(1 << 31); // set LED on
				delay(150);
				PTE->PDOR |= (1 << 31); // set LED off
				delay(150);
			}
			blink = 0;
			x = 0;
			first = 1;
		}
		ADC0->SC1[0] = 0x03;//Channel 3 is selected for single ended ADC (because the ADC on PTE[22] uses channel 3 as input).
		while ( (!ADC0->SC1[0]) & 0x80) {
			//Do nothing
		}
		if (first == 1) {
			initial = ADC0->R[0];//	The value created by the ADC is read from ADCO_R[0] when the conversion is complete.
			first = 0;
			continue;
		} else {
			new = ADC0->R[0];//	The value created by the ADC is read from ADCO_R[0] when the conversion is complete.
			if (abs(new - initial) < 200) {
				continue;
			} else {
				x++;
			}
		}
	}
	return 0;
}

void PORTC_PORTD_IRQHandler(void) {
	switch (PORTC->ISFR)  //If an interrupt is raised on port C.
	{
	case (0b1000):  //If the interrupt is on pin 3 (SW3 is pressed).
		PORTC->PCR[3] |= PORT_PCR_ISF_MASK;
		blink = 1;
		break;

	default:
		PORTC->ISFR |= 0xFFFFFFFF;  //clear the flag.
		break;
	}

}

void delay(unsigned long msec) {
	unsigned long i;
	while (msec > 0) {
		i = 13333;                    // this number means 1ms
		while (i > 0) {
			i = i - 1;
		}
		msec = msec - 1;            // decrements every 1ms
	}
}
