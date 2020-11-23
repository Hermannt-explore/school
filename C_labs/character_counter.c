//This program should read standard input and output the top three most repeated characters with their scores.
//THIS IS NOT YET COMPLETE!!! IT ONLY DISPLAYS IF THERE IS REPETITION.
#include <stdio.h>
#include <stdlib.h>
    int main()
    {
    	int i;
	int j;
	int k;
	int n;
	int flag=0;
	//store the first number in n.
	scanf("%d", &n);
  	//create pointer and point it to the beginning of a 20 byte array in memory.
	int *p;
	p=malloc(20*sizeof(int));
	//place intergers from standard input in the array spots we allocated to the pointer p.
	for (i=0; i<n; ++i){
 		scanf("%d", p+i);
		printf("%d\n", *(p+i)); 
	}
	//compare the values in the array.
	for(j=0; j<n; ++j){
		for (k=(j+1); k<n; ++k) {
			if (*(p+j) == *(p+k)){
			printf("YES\n");	
			flag=1;
			break;
			}
		}
		if(flag == 1){
		break;
		}
	}
	if (flag == 0){
	printf("NO\n");
	}
	//free up the memory we allocated to the pointer p.
	free(p);
    }
