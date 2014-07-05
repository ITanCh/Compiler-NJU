int min(int a[10], int n)
{
int i = 1, j = n;
int min = 0;
while(i<j) {
if(a[i] < a[min]) {
min = i;
}
i = i+1;
}

return a[min];
}

int main()
{
int array[10];
int index = 0, size = 10;
while(index<size)
{
int ti = index*index*index;
array[index] = ti - ti/size*size;
index = index + 1;
}
write(min(array, size));
}

