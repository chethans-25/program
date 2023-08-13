#include <stdio.h>
#include <math.h>

int rem(int x, int y){
    int REM=x-y*(x/y);
    return REM;
}

int powerr(int a,int b){
int p,x=b;
if (x<=0) return 1;
else if(x==1) return a;
else return a*powerr(a,x-1);
}

void main(){
    int i=8,j=100;
    // int remm=rem(j,i);
    int p=powerr(2,5);
    printf("\n%d\n",p);
}