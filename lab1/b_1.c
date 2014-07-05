struct Vector
{
		float x, y;
};

float dotMultiply(struct Vector v1: struct Vector v2)
{
		return v1.x*v2.y - v1.y*v2.x;
}
int main()
{
		stuct Vector v1, v2;
		v1.x = 1.2;
		v1.y = 3.6;
		v2.x = 4.5;
		v2.y = 6.7;
		return dotMultiply(v1, v2));
}
