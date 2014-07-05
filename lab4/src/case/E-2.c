struct Vector
{
int x, y;
};

int crossProduct(struct Vector v11, struct Vector v21)
{
return v11.x*v21.y - v11.y*v21.x;
}

int main()
{
struct Vector v1, v2;
v1.x = 1;
v1.y = 2;
v2.x = 3;
v2.y = 6;
write(crossProduct(v1, v2));
return 0;
}

