
#include<stdio.h>
int checksum(int a[], int m, int k)
{
        int chks=0,i;
        for(i=0;i<m;i++)
                chks+=a[i];
        chks+=k;
        chks=~chks;
        return chks;

}

void main()
{
        printf("Enter length of String\n");
        int m;
        scanf("%d",&m);
        int send[m], recv[m];
        printf("Enter the Sender's string\n");
        int i=0;
        for(i=0; i<m; i++)
                scanf("%d",&send[i]);
        int send_chksum = checksum(send,m, 0);
        printf("Enter the recev's string\n");
        for(i=0; i<m; i++)
                scanf("%d",&recv[i]);
        int recv_chksum = checksum(recv,m, send_chksum);
        printf("Sender's checksum = %d \nRecev's checksum = %d\n", send_chksum, recv_chksum);
        if(recv_chksum==0)
                printf("NO ERROR DETECTED\n");
        else
                printf("ERROR DETECTED\n");
}
