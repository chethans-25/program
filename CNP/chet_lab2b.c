/*

//Cipher Substitution Decryption
#include<stdio.h>
//#include<conio.h>
#include<string.h>
#include<ctype.h>

void main(){
char seq[36]="qwertyuiopasdfghjklzxcvbnm9876543210";
char data[100];
char decoded[100];
int i,j,len,present=0;
printf("\n Enter data:");
gets(data);
len=strlen(data);

for(i=0;i<len;i++){
for(j=0;j<36 && !present;++j){
if(seq[j]==tolower(data[i])){
if(isupper(data[i])) decoded[i]='a'+j;
else if (islower(data[i])) decoded[i]='A'+j;
else decoded[i]='0'+(j-26);
present=1;
}//end of if

}//end of for j

if(!present) decoded[i]=data[i];
else present=0;

}//end of for i

decoded[len]='\0';
printf("\n Decoded string is:%s\n",decoded);

}//end of main

*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
void main(){
    char seq[36]="qwertyuiopasdfghjklzxcvbnm9876543210";
    char data[50],decoded[50];
    int i,j,present=0,len;
    printf("\nEnter Encrypted data: ");
    len=strlen(gets(data));

    for (i=0;i<len;i++){
        for (j=0;j<36 && !present ;j++){
            if (seq [j]==tolower(data[i])){
                if (isupper(data[i])) decoded[i]='a'+j;
                else if (islower(data[i])) decoded[i]='A'+j;
                else decoded[i]='0'+j-26;
                present=1;
            }//end of if
        }//end of for j
        if(!present) decoded[i]=data[i];
        else present=0;
    }//end of for i
    decoded[len]='\0';
    printf("\nDecrypted message is %s",decoded);
}//end of main