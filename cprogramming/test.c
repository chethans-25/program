#include<stdio.h>
#include<string.h>
void main(){
    int x=123;
    char X[10];
    //strcpy(X,x);
    sprintf(X,"%d",x);
    printf("\n%s\n",X);
    printf("\n%d\n",strlen(X));

}