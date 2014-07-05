struct Complex
{

	int real, image;
};
int main()
{
	struct Complex c;
	c.real = 3;
	c.image = 4;
	write(c.real);
	write(c.image);
	return 0;
}

