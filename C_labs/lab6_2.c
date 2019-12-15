#include<stdio.h>
#include<stdlib.h>
void main(){
int i;
char initkey[6];
char key[5];
char c;
FILE *in, *enc;
in=fopen("input.txt", "r");
enc=fopen("out.txt", "w");
if((in == NULL) | (enc == NULL)){exit;}

printf("PLease enter the key : ");
for(i=0; i<6; i++){
	scanf("%c", &initkey[i]);
}
if(initkey[0] == '\n'){
	for(i=0; i<5; i++){
		key[i] = 'a';
	}
}
else{
	for(i=0; i<5; i++){
		key[i] = initkey[i];
	}

}
i=0;
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
}
