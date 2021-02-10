#include<stdio.h>
#include<string.h>
long int gcd(long int a,long int b){
	if(a==0) return b;
	if(b==0) return a;
	return gcd(b,a%b);
}
long int isprime(long int a){
	int i;
	for(i=2;i<a;i++){
		if(a%i==0) return 0;
	}
	return 1;
}
long int de_encrypt(long int ch,long int n, long int k){
	long int i,temp=ch;
	for(i=1;i<k;i++)
		temp=(temp*ch)%n;
	return temp;
}
int main(){
	long int i,p,q,d,e,phi,n,ch[100]; int len;
	char txt[50];
	printf("\nEnter the text to be encrypted:");gets(txt);
	len=strlen(txt);
	do{
		p=rand()%30;}while(!isprime(p));
	do{
		q=rand()%30;}while(!isprime(q));
	n=p*q;
	phi=(p-1)*(q-1);
	do{
		e=rand()%phi;
	}while(gcd(phi,e)!=1);
	do{
		d=rand()%phi;
	}while((d*e)%phi!=1);
	printf("\nTwo prime numbers p= %ld and q= %ld\nn=(p*q)=%ld*%ld=%ld\n",p,q,p,q,p*q);
	printf("\n(p-1)*(q-1)=%ld\n",phi);
	printf("\nPublic key (n,e):(%ld,%ld)",n,e);
	printf("\nPrivate key (n,d):(%ld,%ld)",n,d);
	for(i=0;i<len;i++)
		ch[i]=de_encrypt(txt[i],n,e);
	printf("\nEncrypted message: ");
	for(i=0;i<len;i++)
		printf("%ld",ch[i]);
	for(i=0;i<len;i++)
                txt[i]=de_encrypt(ch[i],n,d);
	 printf("\nDecrypted message: ");
        for(i=0;i<len;i++)
                printf("%c",txt[i]);
	printf("\n");
	return 0;
}






