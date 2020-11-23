//This program decrypts an encrypted file using the user provided key.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
int i;
char initkey[6];
char key[6];
char c;
char name[100];
FILE *out, *enc;
/*Opnening prompt*/
printf("Please enter name of file to decrypt\n");
fgets(name, 100, stdin);		//Read file name from user.
name[strcspn(name, "\n")] = '\0';	//Discard characters after the new line.
enc = fopen(name, "r");			//Open file.
if(enc == NULL ){printf("file does not exist on this directory!"); exit(0);}
out=fopen("decrypted.txt", "w");	//Create ouptu file.	

printf("PLease enter 5-character encryption key : ");
for(i=0; i<6; i++){
	scanf("%c", &initkey[i]);
	if(initkey[0] == '\n')
	{	break;
	}
	if( (initkey[1] == '\n') |  (initkey[2] == '\n') |  (initkey[3] == '\n') |  (initkey[4] == '\n') )
	{printf("Decryption failed! Key did not contain 5 characters.\n"); exit(0);}	
}
/*Use key aaaaa if no key was entered*/
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
/*File decryption*/
while( (c=fgetc(enc)) != EOF){
	if( i==5 ){
	i=0;
	}
	c= c ^ key[i];
	fputc(c, out);
	i++;
}
fclose(out);
fclose(enc);
/*closing prompts*/
printf("your file \"");
printf("%s", name); 
printf("\" has been decrypted with your key ");
for(i=0; i<6; i++){
	printf("%c", key[i]);
}
printf("your decrypted file is named decrypted.txt\n");
}
