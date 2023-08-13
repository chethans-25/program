#include<stdio.h>
#include<string.h>
#define N strlen(gen_poly)
char data[30];
char check_value[30];
char gen_poly[30];
int data_length,i,j;
void crc_1();
void XOR(){
    for(j = 1;j < N; j++)
    check_value[j] = (( check_value[j] == gen_poly[j])?'0':'1');
   
}
void receiver(){
    printf("\nEnter the received data: ");
    scanf("%s", data);
    printf("Data received: %s", data);
    crc_1();
    for(i=0;(i<N-1) && (check_value[i]!='1');i++);
        if(i<N-1)
            printf("\nError detected\n\n");
        else
            printf("\nNo error detected\n\n");
}

void crc_1(){
    for(i=0;i<N;i++)
        check_value[i]=data[i];
    do{
        if(check_value[0]=='1')
            XOR();
        for(j=0;j<N-1;j++)
            check_value[j]=check_value[j+1];
        check_value[j]=data[i++];
    }while(i<=data_length+N-1);
}

int main()
{
    printf("\nEnter data to be transmitted: ");
    scanf("%s",data);
    printf("\n Enter the Generating polynomial: ");
    scanf("%s",gen_poly);
    data_length=strlen(data);
    for(i=data_length;i<data_length+N-1;i++)
        data[i]='0';
    printf("\n Data padded with %d zeros : %s",N-1,data);
    crc_1();
    printf("\nCRC or Check value is : %s",check_value);
    for(i=data_length;i<data_length+N-1;i++)
        data[i]=check_value[i-data_length];
    printf("\n Final data to be sent : %s",data);
    receiver();
    return 0;
}

/*

#include<stdio.h>
#include<string.h>
#define N strlen(gen_poly)
char data[30];
char check_value[30];
// char gen_poly[]={1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};
char gen_poly[30];
int data_length,i,j;
void crc_1();
void XOR(){
    for(j = 1;j < N; j++)
    check_value[j] = (( check_value[j] == gen_poly[j])?'0':'1');
   
}
void receiver(){
    printf("\nEnter the received data: ");
    scanf("%s", data);
    printf("Data received: %s", data);
    crc_1();
    for(i=0;(i<N-1) && (check_value[i]!='1');i++);
        if(i<N-1)
            printf("\nError detected\n\n");
        else
            printf("\nNo error detected\n\n");
}

void crc_1(){
    for(i=0;i<N;i++)
        check_value[i]=data[i];
    do{
        if(check_value[0]=='1')
            XOR();
        for(j=0;j<N-1;j++)
            check_value[j]=check_value[j+1];
        check_value[j]=data[i++];
    }while(i<=data_length+N-1);
}

int main()
{
    printf("\nEnter data to be transmitted: ");
    scanf("%s",data);
    printf("\n Enter the Generating polynomial: ");
    scanf("%s",gen_poly);
    data_length=strlen(data);
    for(i=data_length;i<data_length+N-1;i++)
        data[i]='0';
    printf("\n Data padded with n-1 zeros : %s",data);
    crc_1();
    printf("\nCRC or Check value is : %s",check_value);
    for(i=data_length;i<data_length+N-1;i++)
        data[i]=check_value[i-data_length];
    printf("\n Final data to be sent : %s",data);
    receiver();
    return 0;
}



*/