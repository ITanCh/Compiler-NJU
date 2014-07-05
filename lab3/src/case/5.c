int main()
{
	int i=-1;
	int j=1;
	int m=j;
	int n=i+j;
	m=i;
	if(i>0&&j<=0||m>0&&n!=0)
		write(1);
	else
		write(0);
	if(m>0)
		write(2);
	else 
		write(3);
	return 0;
}
