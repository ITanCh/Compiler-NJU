int main()
{
int n = read();
int i = 2;
while(i<=n) {
int r = 2;
int half = i / 2;
int isPrime = 1;
while(r <= half) {
int remainr = i - i / r * r;
if(remainr == 0)
isPrime = 0;
r = r + 1;
}
if(isPrime == 1)
write(i);
i = i+1;
}
return 0;
}
