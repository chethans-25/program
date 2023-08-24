#include<stdio.h>
#include<string.h>
struct node{
int set;
}node[100];

struct edge{
int n1,n2,sel,d;
}e[100];

int ec=0;
void getdata(int index, int total){
    int i;
    for(i=1+index;i<total;i++){
        printf("\nEnter distance between Vertex %c and %c:",index+65,i+65);
        scanf("%d",&e[ec].d);
        e[ec].n1=index;
        e[ec].n2=i;
        ++ec;
    }
}

void init(int total){
    int i;
    for(i=0;i<total;i++) node[i].set=i;
    for(i=0;i<ec;i++) e[i].sel=-1;
}

void sort(){
    int i,j;
    struct edge temp;
    for(i=0;i<ec-1;i++)
        for(j=0;j<ec-i-1;j++)
            if(e[j].d>e[j+1].d){
                temp=e[j];
                e[j]=e[j+1];
                e[j+1]=temp ;
            }
}

void main(){
    int i,total,j,k,m,n,esel=0,nl,nr;
    printf("\nEnter the number of nodes:");
    scanf("%d",&total);
    for(i=0;i<total;i++) getdata(i,total);
    init(total);
    sort();
    printf("\nThe Sorted order of edges:");
    for(i=0;i<ec;i++)
        printf("\nedge: %d, first node: %c, second node: %c, distance: %d",i,e[i].n1+65,e[i].n2+65,e[i].d);
    i=0;
    do{
        e[i].sel=1;
        nl=e[i].n1;
        nr=e[i].n2;
        if(node[nl].set==node[nr].set)
            e[i].sel=-1;
        else {
            esel++;
            m=node[nl].set;
            k=node[nr].set;
            for(n=0;n<total;n++)
                if(node[n].set==k)
                    node[n].set=m;
        }
        i++;
    }
    while(esel<(total-1));
    printf("\nMinimum Spanning Tree is:");
    for(i=0;i<ec;++i)
        if(e[i].sel==1)
            printf("\n%c<------->%c distance %d",e[i].n1+65,e[i].n2+65,e[i].d);
}
