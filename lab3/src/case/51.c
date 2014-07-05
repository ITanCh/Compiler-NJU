int main()
{

	int a = 3, b = 4, i = 0, sum = 0;
	int c, d, e;
	int array[150];
	d = a * a;
	e = b * b;
	if ( -1 || d + e > 0)
		i = (a * a - b * b + d * e) / (a - 8);
	c = - ( 7 - a * (1+2) - (36/(10-1)) * b + d * e);
	i = c - c;
	while (i < 100+50)
	{

		array[i] = 1;
		i = i + 1;

	}
	i = array[0] + d - 1 - d;
	while (i < -1 * (c - b * b + a * a))
	{

		int k = a + 4 - b;
		int j = d, l = k - 1;
		while (j > a + b - 10 + 3)
		{

			int f = 0;
			array[i/10] = array[i/10] + (j*3);
			if (l == 2) array[i/10] = array[i/10] - (2 + j*3);
			if (i > 100)
				f = j / 2 - 1;
			else
				array[i/10] = array[i/10] + j;
			f = f - 1;
			j = j / 2 - 1;

		}
		if (b + sum < d || e)
			i = i + 1;

	}
	i=0;
while (i < 150)
{

	sum = sum + array[i];
	i = i + 1;

}
write(sum);
return 0;

}
