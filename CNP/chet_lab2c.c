/*
//Encryption by transposition method
#include<stdio.h>
#include<string.h>

void main(){
char data[100];
char wrd[]="MEGABUCK";
char cipher[20][8];
int seq[8];
int i,j,k,cnt;
for (i=0;i<len;i++){
cnt=0;
for(j=0;j<8;j++)
if(wrd[i]>wrd[j]) ++cnt;
seq[i]=cnt;
}//end of for i
printf("\n Enter data :");
gets(data);
cnt=strlen(data);
for(i=0;i<cnt;i++) cipher[i/len][i%len]=data[i];
if(i%len!=0){
for(j=i%len;j<len;j++){
cipher[i/len][j]='.';
cnt++;
}//end of for j
}//end of if
printf("\n Encrypted data :\n");
for(i=0;i<8;i++){
for(j=0;j<8;j++)
if(seq[j]==i) break;
for(k=0;k<cnt/8||k==0;k++) printf("%c",cipher[k][j]);
}//end of for i
printf("\n");
}//end of main
*/

//modified code

//Encryption by transposition method
#include<stdio.h>
#include<string.h>


void main(){
char data[100];
char wrd[]="MEGABUCK";
int len=strlen(wrd);
char cipher[20][len];
int seq[len];
int i,j,k,cnt;

for (i=0;i<len;i++){
    cnt=0;
    for(j=0;j<len;j++)
        if(wrd[i]>wrd[j]) ++cnt;
    seq[i]=cnt;
}//end of for i
printf("\n Enter data :");
cnt=strlen(gets(data));
for(i=0;i<cnt;i++) cipher[i/len][i%len]=data[i];
if(i%len!=0){
    for(j=i%len;j<len;j++){
        cipher[i/len][j]='.';
        cnt++;
    }//end of for j
}//end of if
printf("\n Encrypted data :\n");
for(i=0;i<len;i++){
    for(j=0;j<len;j++)
        if(seq[j]==i) break;
    for(k=0;k<cnt/len||k==0;k++)
        printf("%c",cipher[k][j]);
}//end of for i
printf("\n");

}//end of main
