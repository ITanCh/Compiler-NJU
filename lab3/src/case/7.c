struct Ins{
	int x;
	int y;
};
struct Operands
{
	int o1;
	int o2;
	int a[5];
	struct Ins s[5];
};
int add(struct Operands temp)
{
	return (temp.o1 + temp.a[3]+temp.s[3].y);
}
int main()
{
	int n;
	struct Operands op;
	op.o1 = 1;
	op.o2 = 2;
	op.a[3]=4;
	op.s[3].y=5;
	n = add(op);
	write(n);
	return 0;
}
