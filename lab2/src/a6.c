struct Vector
{

	float x, y;

};
float dotmultiply(struct Vector v1, struct Vector v2)
{

	return v1.x*v2.y - v1.y*v2.x;

}

int main()
{

	struct Vector sv1, sv2;
	dotmultiply(sv1, sv2) = 1.434;

}

