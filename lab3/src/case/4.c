struct s
{
	int x;
	int y;
	int z;
};

int add(int a,int b,int c)
{
	write(a-b-c);
	return 0;
}

int main()
{
	int n=read();
	int m=read();
	int l=0;
	int o=m;
	struct s s1;
	if(n>0 && m>0)
	{
		s1.x=1;
		s1.y=2;
		s1.z=3;
	}
	else if(n==0)
	{
		s1.x=s1.y=s1.z=0;
	}
	else
	{
		s1.x=-1;
		s1.y=-2;
		s1.z=-3;
	}
	n=add(s1.x,s1.y,s1.z);
	return 0;
}
