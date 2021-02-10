#include<stdio.h>
#include<math.h>
long long int power(long long int a,long long int b,long long int p){
	if(b==1) return a;
	else return ((long long int)pow(a,b))%p;
}
int main(){
	long long int p,g,x,a,y,b,ka,kb;
	p=23;
	g=9;
	a=4;
	b=3;
	printf("\nThe value of P is : %lld\n",p);
	printf("\nThe value of G is : %lld\n",g);
	printf("\nThe private key a for ALice is : %lld\n",a);
	printf("\nThe private key b for Bob is : %lld\n",b);
	x=power(g,a,p);
	y=power(g,b,p);
	ka=power(y,a,p);
	kb=power(x,b,p);
	printf("\nShared key for Alice is : %lld\nShared key for Bob is: %lld\n",x,y);
	printf("\nSecret key for Alice is : %lld\nSecret key for Bob is: %lld\n",ka,kb);
	return 0;
}

/*
#include<stdio.h>
#include<stdlib.h>
int compute(int ch, int k, int q)
{
	int temp=ch,i;
	for(i=1;i<k;i++)
		temp=(temp*ch)%q;
	return temp;
}
int main()
{
	int q=23;
	int a=6,b=15,g=5;
	int a1=compute(g,a,q);
	int a2=compute(g,b,q);
	int b1=compute(a2,a,q);
	int b2=compute(a1,b,q);
	printf("Alice private key : %d\tshared key: %d\tKey: %d\n",a,a1,b1);
	printf("Bob private key : %d\tshared key: %d\tKey: %d\n",b,a2,b2);

}*/
