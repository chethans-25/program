#include <stdio.h>
#include <string.h>
#define DLE 16
#define STX 2
#define ETX 3

int main()
{   char ch,array[100]={DLE,STX};
    int i=2,j=0;
    printf("\n Enter the data stream (ctrl+B->STX,ctrl+C->ETX,ctrl+P->DLE):\n");
    
    do {
          scanf("%c",&ch);
          if(ch==DLE || ch==STX || ch==ETX)
           array[i++]=DLE;
          array[i++]=ch;
          
        }while(ch!='\n');
    array[i++]=DLE;
    array[i++]=ETX;
    
    printf("\nThe stuffed stream is\n");
    printf("DLE");
    printf("STX");
    
    for(j=2;j<i;j++){
        if(array[j]==16)
           printf("DLE");
          else if (array[j]==2)
           printf("STX");
          else if (array[j]==3)
           printf("ETX");
          else printf("%c",array[j]);
    }
    
    //DESTUFFING
    printf("\n The destuffed data is \n");
    for(j=2;j<i-2;j++){
        if(array[j]==16)
            j++;
        if(array[j]==16)
           printf("DLE");
        else if (array[j]==2)
           printf("STX");
        else if (array[j]==3)
           printf("ETX");
        else printf("%c",array[j]);
    }
    return 0;
}