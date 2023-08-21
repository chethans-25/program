#include<stdio.h>
#include<string.h>
void main(){
    char a[50]="01111110",r[50],ch;
    int i=8,j=0,k=0,c=0;
    printf("\nEnter data stream:");
    do
    {
        scanf("%c",&ch);
        if(ch=='1') c++;
        else c=0;
        a[i++]=ch;
        if(ch==5){
            a[i++]='0';
            c=0;
        }
    } while (ch!='\n');
    strcat(a,"01111110");
    printf("\nTransmitted data after bit stuffing is : %s",a);

    j=strlen(a);
    c=0;
    for (i=8;i<j-8;i++){
        if(a[i]=='1') c++;
        else c=0;
        r[k++]=a[i];
        if(c==5){
            i++;
            c=0;
        }
    }
    printf("\nThe destuffed message is : %s",r);
    
}