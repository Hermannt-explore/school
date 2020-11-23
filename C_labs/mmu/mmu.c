#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void){

	//Incrementation
	int i;
	int j;	
	int k;
	int count=0;
	int tlb_misses;
	int tlb_hits=0;
	//Var
	int vr_num;
	int pg_num;
	int offset;
	int frm_num;
	int tmp;
	int loc;
	//Status
	int tlb_miss;
	int pg_fault;
	int tlb_full;
	int new_and_full;
	//Buffers
	char vr_addr[80];
	signed char value;
	char p[1]="%";
	//Pointers
	FILE *addr;
	FILE *bk_str;
	FILE *csv;
	//Structures
	struct page{
		int frm_num;
		int valid;
	};
	struct page pg_table[256];
	struct TLB{
		int pg_num;
		int frm_num;
		int valid;
	};	
	struct TLB tlb[16];
	struct frame{
		signed char frame[256];
		int valid;
	};
	struct frame phys_mem[256];
	
	//FILE OPENING
	addr = fopen("addresses.txt", "r");
	bk_str = fopen("BACKING_STORE.bin", "r");
	csv = fopen("output.csv", "w");	
	//FILE AVAILABILITY CHECK
	if( ( addr==NULL ) || ( bk_str==NULL )){
		printf("file_error\n");
		exit(0);
	}

	//SETUP	(Set status of each location in all structures to available)
	for( j=0; j<256; j++ ){
		pg_table[j].valid = 1;
		phys_mem[j].valid = 1;
	}
	for( j=0; j<16; j++ ){
		tlb[j].valid = 1;
	}

	//Main Loop
	while( (fgets( vr_addr, 80, addr)) != NULL ){	
		tlb_miss=0;
		pg_fault=0;
		tlb_misses=0;
		tlb_full=0;
		vr_num = (atoi(vr_addr) &65535);	
		offset = vr_num & 255;
		tmp = vr_num & 65280;
		pg_num = tmp >> 8;
	
		//CHECK TLB FIRST
		for( i=0; i<16; i++ ){
			if( (tlb[i].pg_num == pg_num) && (tlb[i].valid == 0) ){
				frm_num = tlb[i].frm_num;
				tlb_hits++;
				tlb_miss=0;
				pg_fault=0;
				break;
			}	
			else if( (tlb[i].pg_num != pg_num) && (tlb[i].valid == 0) ){
				tlb_misses++;
				tlb_miss=1;
			}
			else if( (tlb[i].pg_num == pg_num) && (tlb[i].valid == 1) ){
				tlb_miss=1;
				break;	
			}	
			else{
				tlb_miss=1;
				break;
			}
		}
		if(tlb_misses == 16){
			tlb_full=1;
		}

		//CHECK PG_TABLE
		if( tlb_miss == 1 ){
			if( (pg_table[pg_num].valid == 0) ){	
				frm_num = pg_table[pg_num].frm_num;
				pg_fault=0;			  
			}
			else{
				pg_fault=1;
			}
		}

		//IF PAGE FAULT
		if( pg_fault == 1 ){				
			fseek(bk_str, pg_num*256, SEEK_SET);	//Find correct page in Backing store
			for(k=0; k<256; k++){			//Find empty  spot in physical memory
				if(phys_mem[k].valid==1){
					fread(phys_mem[k].frame, sizeof(phys_mem[k].frame), 1, bk_str);	//Insert page in frame		
					phys_mem[k].valid = 0;
					frm_num=k;
					new_and_full=0;
					break;
				}
			}
			
			//IF TLB NOT FULL
			if( tlb_full == 0 ){
 				//TBL UPDATE
				for ( j=0; j<16; j++ ){
					if( tlb[j].valid == 1){		//Valid to insert frame number
						tlb[j].frm_num = frm_num;
						tlb[j].pg_num = pg_num;
						tlb[j].valid = 0;
						break;
					}
				}
				// PG_TABLE UPDATE
				if( pg_table[pg_num].valid == 1 ){	//Valid to insert frame number
					pg_table[pg_num].frm_num = frm_num;	
					pg_table[pg_num].valid = 0;
				}
			}
			//IF TLB FULL
			else{	
				//TLB UPDATE (FIFO)
				for(k=0; k<15; k++){
 					tlb[k].frm_num = tlb[k+1].frm_num;			
 					tlb[k].pg_num = tlb[k+1].pg_num;
 				}
 				tlb[15].frm_num = frm_num;
 				tlb[15].pg_num = pg_num;
 				//PG_TABLE UPDATE
				if( pg_table[pg_num].valid == 1 ){	//Valid to insert frame number
					pg_table[pg_num].frm_num = frm_num;	
					pg_table[pg_num].valid = 0;
				}
			}
			//OUTPUT VALUE	
			value = phys_mem[frm_num].frame[offset];
//printf("%d\n", value);
			loc = (frm_num << 8) + offset;	//Physical address		
			count++;	//number of page faults
		}
		
		//IF NO PAGE FAULT
		else{
			//OUTPUT VALUE
			value = phys_mem[frm_num].frame[offset];
//printf("%d\n", value);
			loc = (frm_num << 8) + offset;	//Physical address
		}
	fprintf(csv, "%d,", vr_num);	//Logical address
	fprintf(csv, "%d,", loc);	//Physical address
	fprintf(csv, "%d", value);	//value
	fprintf(csv, "\n");
	}
	
printf("Page-fault rate: %.1f%c\n", (count/10.0), p[0]);
printf("TLB hit rate:  %.1f%c\n", (tlb_hits/10.0), p[0]);

fclose(addr);
fclose(bk_str);
fclose(csv);
return 0;

}
