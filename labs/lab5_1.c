#include <stdio.h>
#include <stdlib.h>
    int main()
    {
    	int i;
	int j;
	int k;
	char n[11];
	int count=0;
	int record=0;
	//enter inputs in the array
	while(i<11){
		scanf("%c", &n[i]);
		if((n[i]!= '1') & (n[i]!= '0') & (n[i]!= ' ')) {
		printf("invalid string\n");
		exit(0);
		}
		if(n[i] == ' '){
			break;
		}
		i++;
	}
	//compare elements in the array	
	for(j=0; j<(i+1); j++){	
		if(n[j] == '1'){
		count = 1;
		for (k=(j+1); k<(i+1); k++){	
			//increment count if there are two consecutive 1's
			if(n[k] == '1'){
				count= count+1;
			}	
			//check if the current count is greater than the record count of consecutive 1's
			else{
				if(record<count){
				record=count;
				}
			break;
			}
		}
		}
		else{
			continue;
		}
	}		
	//print the record number of consecutive 1's
	printf("%d\n", record);
		
}
