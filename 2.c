#include<stdio.h>
struct node{
int dist[20],from[20];}rt[10];
int main(){
int i,j,k,cm[10][10],c=0,n;
printf("\nEnter the number of nodes: ");scanf("%d",&n);
printf("\nEnter the cost matrix:\n");
for(i=0;i<n;i++)
	for(j=0;j<n;j++){
		scanf("%d",&cm[i][j]);
		cm[i][i]=0;
		rt[i].dist[j]=cm[i][j];
		rt[i].from[j]=j;
}
do{
c=0;
for(i=0;i<n;i++)
	for(j=0;j<n;j++)
		for(k=0;k<n;k++){
			if(rt[i].dist[j]>cm[i][k]+rt[k].dist[j]){
				rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
				rt[i].from[j]=k;c++;
				}
			}
		}while(c!=0);
for(i=0;i<n;i++){
	printf("\nFor router %d:\n ",i+1);
	for(j=0;j<n;j++){
		printf("\nNode %d via %d: Distance=%d\n",j+1,rt[i].from[j]+1,rt[i].dist[j]);
	}printf("\n");
}
}


