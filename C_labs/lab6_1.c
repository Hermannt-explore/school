#include<stdlib.h>
#include<stdio.h>

int main()
{
int max = 100;
char c;
int rec;
int sixteen = 16;
FILE *in;
FILE *out;
in = fopen("lab61.txt", "r");
out = fopen("lab61out.txt", "w");
if ( (in == NULL) | (out == NULL)) {
exit;
}
while( (c=fgetc (in)) != EOF){
	if(rec == max){
		fprintf(out, "%d", sixteen);
		fprintf(out, "%c", c);
		rec=0;
		continue;
	}	
	if(c == '\n'){
		fprintf(out, "%d", sixteen);
	}	
	else{
		fprintf(out, "%c", c);
	}
	rec++;
}
	fclose(in);
	fclose(out);

}
