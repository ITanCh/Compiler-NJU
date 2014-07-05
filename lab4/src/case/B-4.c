int fib(int n) {
	if(n == 0)
		return 1;
	else if(n == 1)
		return 1;
	else
		return fib(n-1)+fib(n-2);
}

int main() {
	write(fib(5));
	write(fib(4));
	write(fib(3));
	write(fib(2));
	write(fib(1));
	return 0;
}

