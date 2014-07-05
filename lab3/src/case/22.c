int main()
{

	int s, p, m, n = 10;
	while(n < 100)
	{

		p = 1;
		s = 0;
		m = n;
		while(m != 0)
		{

			p = p * (m - (m / 10) * 10);
			s = s + (m - (m / 10) * 10);
			m = m / 10;

		}
		if(s > p)
			write(n);
		n = n + 1;

	}
	return 0;

}
