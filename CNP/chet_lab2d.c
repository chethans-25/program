//Decryption by transposition method
#include<stdio.h>
#include<string.h>
void main(){
char data[100];
char wrd[]="MEGABUCK";
int len=strlen(wrd);
char cipher[20][len];
int seq[len];
int i,j,cnt,c;

for(i=0;i<len;i++){
    cnt=0;
    for(j=0;j<len;j++)
        if(wrd[i]>wrd[j]) ++cnt;
    seq[i]=cnt;
}
printf("\nEnter data :");
cnt=strlen(gets(data));
if (cnt%len!=0)
    printf("\nError: Invalid Input");
else {
    for(i=0;i<len;i++){
        for(c=0;c<len;c++)
            if(seq[c]==i) break;
        for(j=0;j<cnt/len;j++)
            cipher[j][c]=data[i*(cnt/len)+j];
    }

    for(j=0;j<len;j++){
        if(cipher[cnt/len-1][j]=='.')
            cipher[cnt/len][i%len]=' ';
    }

    printf("Decrypted data:");
    for(i=0;i<cnt;i++)
        if(cipher[i/len][i%len]!='.')
            printf("%c",cipher[i/len][i%len]);

    printf("\n");

}
}
