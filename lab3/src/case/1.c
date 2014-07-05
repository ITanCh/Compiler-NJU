int b;
int main()
{
	int n;
	int a=0;
	b=3;
	n = read();
	if (n > 0) write(1);
	else if (n < 0) write (-1);
	else write(0);
	if(a>0&&b<=0)
		write(1);
	else
		write(0);
	if(a<b || b>=n)
		write(1);
	else
		write(0);
	if(a==b || b!=n)
		write(1);
	else
		write(0);

	return 0;
}
