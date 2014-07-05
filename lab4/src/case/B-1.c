int main()
{
int year = read();
if(year <= 0)
write(-1);
else {
int remain4 = year - (year/4)*4;
int remain100 = year - (year/100)*100;
int remain400 = year - (year/400)*400;
if(remain4 != 0)
write(0);
else if(remain400 == 0)
write(1);
else if(remain100 == 0)
write(0);
else
write(1);
}
return 0;
}

