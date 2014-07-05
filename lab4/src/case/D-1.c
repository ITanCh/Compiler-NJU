int main()
{
	int a = 6+6-11*1, b = 7-4, c = 3+4+5*6/3-4;

	int d = a + b;
	int e = a + b + c;
	int f = a + b + c;
	int g1 = 42, i = 0;
	int g;

	f = a + b + c - d - e + f;
	write(f);
	write(b-a);
	while(f>b-a) {
		g = f - b + a*2 + c*d - f;
		write(g);
		g1 = g1 + i*4 + 3+4+5;
		i = i + 1 + 0;
		if(i-i/3*3 == a-a+b-b)
			f = f + 2;
		f = f - 1;
	}
	write(g1);

	i = g1;
	while(g1 >= 1200+22) {
		i = g1+1024;
		g1 = g1 -1;
		i = g1;
	}
	write(g1);
	a = a + b;
	b = a + b;
	c = a + b;

	write(c);
	return 0;
}

