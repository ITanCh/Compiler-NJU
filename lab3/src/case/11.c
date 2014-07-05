int main()
{

	int a = 3, b = 4, c;
	c = a * a + b * b;
	write(c);
	c = (a + c) / b;
	write(c);
	c = a+b;
	a = a + b;
	b = a - b;
	a = a - b;
	c= a-b;
	b = ((a - b) * 2 - 1) + (a / b) * (2 * (3 + b));
	write(a);
	write(b);
	return 0;

}
