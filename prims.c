//program for prims algorithm
#include<stdio.h>
#define I 32767
int cost[8][8]={
    {I,I,I,I,I,I,I,I},
    {I,I,25,I,I,I,5,I},
    {I,25,I,12,I,I,I,10},
    {I,I,12,I,8,I,I,I},
    {I,I,I,8,I,16,I,14},
    {I,I,I,I,16,I,20,18},
    {I,5,I,I,I,20,I,I},
    {I,I,10,I,14,18,I,I},
};
int near[8]={I,I,I,I,I,I,I,I};
int t[2][6];//for answer i.e spanning tree edges 7-1=6

int main(){
    int i,j,k,u,v,n=7,min=I;
    //Initial steps
    //find minimum cost edge from upper triangular part
    for(i=1;i<=n;i++){
        for(j=i;j<=n;j++){
            if(cost[i][j]<min){
                min=cost[i][j];
                u=i;v=j;//store that edge
            }
        }
    }

    t[0][0]=u;t[1][0]=v;
    near[u]=near[v]=0;//to show that this are included
    //updeting all vertices (near array) by checking they are nearer to whom u or v
    for(i=1;i<=n;i++){
        if(near[i]!=0){
        if(cost[i][u]< cost[i][v])
            near[i]=u;
        else
            near[i]=v;
        }
    }

//repeted code 
// select minimum edge from near mark it as '0'  update near 
//we got one edge so need 5 now

for(i=1;i<n-1;i++){
    //find minimum from near
    min=I;
    for(j=1;j<=n;j++){
        if(near[j]!=0 && cost[j][near[j]] < min){
            min=cost[j][near[j]];
            k=j;
        }
    }
    //writing the minimum edge in t
    t[0][i]=k;
    t[1][i]=near[k];
    //mark the near to 0
    near[k]=0;//included

    //ubdating near array by checking whether they are near to k
    for(j=1;j<=n;j++){
        if(near[j]!=0 && cost[j][k]<cost[j][near[j]]){
            near[j]=k;
        }  
    }
}

//printing spanning tree
printf("\nMin cost spanning tree\n");

for(i=0;i<n-1;i++){
    printf("(%d , %d)\t",t[0][i],t[1][i]);
}
return 0;
}
