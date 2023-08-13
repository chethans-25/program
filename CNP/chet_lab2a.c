/*
//Cipher Substitution Encryption
#include<stdio.h>
//#include<conio.h>
#include<string.h>
#include<ctype.h>
void main()
{
char seq[36]="qwertyuiopasdfghjklzxcvbnm1234567890";
char data[50];
char encoded[50];
int i,j,len;
printf("\nEnter data:");
// gets(data);
// len=strlen(data);
len=strlen(gets(data));

for(i=0;i<len;i++){
if(isupper(data[i])) {encoded[i]=seq[data[i]-'A'];}
else if(islower(data[i])) {encoded[i]=toupper(seq[data[i]-'a']);}
else if(isdigit(data[i])) {encoded[i]=seq[data[i]-'0'+26];}
else {encoded[i]=data[i];}
}//end of for

encoded[len]='\0';
printf("\nencoded string is:%s\n",encoded);
}

*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>

void main(){
    char seq[36]="qwertyuiopasdfghjklzxcvbnm9876543210";
    char data[50];
    char encoded[50];
    int i,len;
    printf("\nEnter data to be encoded: ");
    len=strlen(gets(data));

    for (i=0;i<len;i++){
        if (isupper(data[i])) encoded[i]=seq[data[i]-'A'];
        else if (islower(data[i])) encoded[i]=toupper(seq[data[i]-'a']);
        else if (isdigit(data[i])) encoded[i]=seq[data[i]-'0'+26];
        else encoded[i]=data[i];
    }
    encoded[len]='\0';
    printf("\nEncoded string is %s",encoded);
}