#include <stdio.h>

void disp(int arr[],int l){
    for (int i=0;i<l;i++)
    printf("%d ",arr[i]);
}

void bubble_sort(int arr[],int l){
int j=l,i,tmp;
while (j>1){
    for (i=0;i<l-1;i++){
        if (arr[i]>arr[i+1]){
            tmp=arr[i];
            arr[i]=arr[i+1];
            arr[i+1]=tmp;
        }
    }
    j--;
}
// return arr;
}

void main(){
    int arr[]={1,23,54,65,23,42};
    int l=sizeof(arr)/sizeof(arr[0]);
    // printf("%d",arr);
    disp(arr,l);
    bubble_sort(arr,l);
    printf("\n");
    disp(arr,l);
}