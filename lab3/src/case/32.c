int josef(int m)
{
	int a[21];
	int i = 0, j, k = 0;
	while(i < 21)
	{
		a[i] = i + 1;
		i = i + 1;
	}
	i = 0;
	while(i < 21)
	{
		j = 1;
		while(j < m)
		{

			while(a[k] == 0)
			{

				k = (k + 1)-((k + 1) / 21 * 21);

			}
			j = j + 1;
			k = (k + 1)-((k + 1) / 21 * 21);

		}
		while(a[k] == 0)
		{

			k = (k + 1)-((k + 1) / 21 * 21);

		}
		write(a[k]);
		a[k] = 0;
		i = i + 1;

	}
	return 0;
}

int main()
{
	josef(5);
	return 0;
}

