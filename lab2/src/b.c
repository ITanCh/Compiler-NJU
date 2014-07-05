struct Vector
{

	float x, y;

};
float dotMultiply(struct Vector v1, struct Vector v2)
{
	return v1.x*v2.y-v1.y*v2.z;
}

struct Vector2
{

	float x2 = 1.0, y2;
	float y2;
};

struct Vector3
{

	int x3;

};
int main()
{
	float a[10], c[10];
	int Vector3;
	int d[10];
	int i = 0;
	struct Vector sv1;
	struct Vector sv2;
	while(i<10)
	{
		sv1.x = a[i];
		sv1.y = b;
		sv2.x = c[i];

		sv2.y = d[i];
		i = i+1;

		dotMultiply(sv1, sv2);

	}
	return 0;


}

