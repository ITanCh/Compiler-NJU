int main()
{
	int i = 10;
	int j;
	int a[10];
	i=20;
	a[1]=0;
	i=30;
	j=1;
	while(i > 0)
	{
		j=i;
		write(i);
		i = i - 1;
		j=i;
		write(j);
	}
	return 0;
}
