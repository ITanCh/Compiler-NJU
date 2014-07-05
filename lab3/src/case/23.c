int main()
{

	int a[10];
	int i = 0, j = 10, temp;
	while(i < j)
	{

		a[i] = i;
		i = i + 1;

	}
	i = 0;
	while(i < (j / 2))
	{

		temp = a[i];
		a[i] = a[j - i - 1];
		a[j - i - 1] = temp;
		i = i + 1;

	}
	i = 0;
	while(i < j)
	{

		write(a[i]);
		i = i + 1;

	}
	return 0;

}
