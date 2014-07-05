struct Vector
{
	float x, y;

};
int dotmultiply(struct Vector v1, struct Vector v2)
{

	return v1.x*v2.y - v1.y*v2.x;
}
int main()
{
	return 0;
}

