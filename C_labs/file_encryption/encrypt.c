//This program encrypts a file with the user provided key.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
int i;
char initkey[6];
char key[6];
char c;
FILE *in, *enc;
char name[100];
/*opening prompt*/
printf("Please enter name of file to encrypt\n");
fgets( name, 100, stdin);		//Read file name from user.
name[strcspn(name, "\n")] = '\0'; 	//Discard characters after the new line.
in=fopen( name, "r");			//Open file.
if(in == NULL ){printf("file does not exist in this directory!"); exit(0);}
enc=fopen("encrypted.txt", "w");	//Create output file.

printf("PLease enter 5-character encryption key : ");
/*Get key from user*/ 
for(i=0; i<6; i++){
	scanf("%c", &initkey[i]);
	if(initkey[0] == '\n')
	{	break;
	}
	if( (initkey[1] == '\n') |  (initkey[2] == '\n') |  (initkey[3] == '\n') |  (initkey[4] == '\n') )
	{printf("Encryption failed! Your key did not contain 5 characters.\n"); exit(0);}	
}
/*use key aaaaa if no key was entered.*/
if(initkey[0] == '\n'){
	for(i=0; i<5; i++){
		key[i] = 'a';
	}
	key[5] = '\n';
}
else{
	for(i=0; i<5; i++){
		key[i] = initkey[i];
	}
	key[5]= '\n';
}
i=0;
/*File encryption*/
while( (c=fgetc(in)) != EOF){
	if( i==5 ){
	i=0;
	}
	c= c ^ key[i];
	fputc(c, enc);
	i++;
}
fclose(in);
fclose(enc);
/*Closing prompts*/
printf("your file \"");
printf("%s", name); 
printf("\" has been encrypted with your key ");
for(i=0; i<6; i++){
	printf("%c", key[i]);
}
printf("your encrypted file is named encrypted.txt\n");
}
