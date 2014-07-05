int power(int base1, int p1) {
	int ret1 = 1;
	while(p1>0)
	{
		ret1 = ret1 * base1;
		p1 = p1 - 1;
	}
	return ret1;
}

int mod(int number2, int m2)
{
	return number2 - number2 / m2 * m2;
}

int getNumDigits(int number3)
{
	int ret3 = 0;
	if(number3 < 0)
		return -1;
	while(number3 > 0) {
		number3 = number3 / 10;
		ret3 = ret3+1;
	}

	return ret3;
}

int isNarcissistic(int number4)
{
	int numDigits4 = getNumDigits(number4);
	int sum4 = 0;
	int n4 = number4;
	int s4;
	while(n4>0) {
		s4 = mod(n4, 10);
		n4 = (n4 - s4) / 10;
		sum4 = sum4+power(s4, numDigits4);
	}

	if(sum4 == number4)
		return 1;
	else
		return 0;
}

int printHexDigit(int digit6)
{
	if(digit6 < 10)
		write(digit6);
	else
		write(-digit6);
	return 0;
}

int printHex(int number5)
{
	int a5[4];
	int j5 = 0;
	while(j5<4) {
		a5[j5] = mod(number5, 16);
		number5 = number5 / 16;
		j5=j5+1;
	}
	j5 = 3;
	while(j5>=0) {
		printHexDigit(a5[j5]);
		j5=j5-1;
	}
	return 0;
}


int main() {
	int count = 0;
	int i = 9474;
	while(i<9475)
	{
		if(isNarcissistic(i) == 1)
		{
			printHex(i);
			count = count + 1;
		}
		i=i +1;
	}
	return count;
}
