#include<stdio.h>
#include<string.h>

#define N strlen(gp)

int i,j,l;
char data[30],gp[30],cv[30];

void crc();
void XOR();
void receiver();

int main(){
    printf("\nEnter data to be transmitted: ");
    scanf("%s",data);
    printf("\nEnter generator polynomial: ");
    scanf("%s",gp);
    l=strlen(data);
    for (i=l;i<l+N-1;i++) data[i]='0';
    printf("\nData padded with %d zeros at the end is %s",N-1,data);
    crc();
    printf("\nCheck value or CRC is %s",cv);
    for (i=l;i<l+N-1;i++) data[i]=cv[i-l];
    printf("\nFinal data to be transmitted is %s",data);
    receiver();
    return 0;
}

void receiver(){
    printf("\nEnter data received: ");
    scanf("%s",data);
    printf("\nData received is %s",data);
    crc();
    for(i=0;(i<N-1) && (cv[i]!='1');i++);
    if(i<N-1) printf("\nError detected!!");
    else printf("\nNo error detected!!");
}

void crc(){
    for (i=0;i<N;i++) cv[i]=data[i];
    do{
    if (cv[0]=='1') XOR();
    for(j=0;j<N-1;j++) cv[j]=cv[j+1];
    cv[j]=data[i++];
    }while(i<=l+N-1);
}

void XOR(){
    for (j=1;j<N;j++)
    cv[j]=((cv[j]==gp[j])?'0':'1');
}