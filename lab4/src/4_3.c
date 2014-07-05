int func(int a1,int a2,int a3,int a4,int a5)
{
	return a1+a2+a3+a4+a5;
}
int main()
{
	int i=0;
	int j=1;
	int k=2;
	int g=3;
	int h=4;
	int a[10];
	a[5]=5;
	a[3]=func(i,j,k,g,h);
	write(a[3]);
	write(i+j+k);
	return 0;
}
