int main()
{
int a = 10, b = 20, c = 3;
int d = a + b *c -b;
write(d);
d = (a+b) / c;
write(d);
a = a + b;
b = a - b;
a = a - b;
b = (a-b)/2 + (a/b)*2;
write(b);
return 0;
}

