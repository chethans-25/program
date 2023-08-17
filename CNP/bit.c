#include <stdio.h>
#include <string.h>
int main()
{
   char ch;
   char array[50]="01111110",recarray[50];
   int count=0,i=8,j=0,k=0;
   printf("Enter the input string \n");
   do {  scanf("%c",&ch);
         if(ch=='1')
            count=count+1;
         else 
            count=0;
         array[i++]=ch;
         if(count==5)
         {
             array[i++]='0';
             count=0;
         }
       } while (ch!='\n');
    strcat(array,"01111110");
    printf(" \n The stuffed string is:%s",array);


j=strlen(array);
for(i=8;i<j-8;i++)
{
    if(array[i]=='1')
       count++;
    else count=0;
    recarray[k]=array[i];
    k++;
    if(count==5 && array[i+1]=='0')
    {
        i++;
        count=0;
    }
}
printf("\nThe destuffed data is:%s",recarray);

    return 0;
}