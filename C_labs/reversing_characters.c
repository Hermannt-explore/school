#include <stdio.h>
#include <stdlib.h>
    int main()
    {
	int i=0;
	int j=0;
	int k=0;
	int flag=1;
	char valid[10]={'0','1','2','3','4','5','6','7','8','9'};
	char input[10];

		//enter standard input characters in the 'input' array
		while(i<10){
			j=0;
			flag=1;
			scanf("%c", &input[i]);	
			
			//check if the current character from 'input' array is an integer
			while(j<10){
				if(valid[j] == input[i] ){
					flag=0;
					break;
				}
				j++;
			}
			//if the current character is not an integer, break.
			if(flag == 1){
				break;
			}
			i++;
		}

		//copy elements from 'input' array to 'new' array	
		char new[i];
		j=i;
		while(k < j){
			new[k]= (input[(i-1)])-48;
			i--;
			k++;
		}

		//print each elemet of the new array without spaces 
		k=0;
		while(k<j){
			printf("%d", new[k]);
    			k++;
		}
    		//print the new line
		printf("\n");
    }
