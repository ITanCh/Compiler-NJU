struct Vector1
{

	 float x1, y1;
	 int a1, b1;

};

struct Vector2
 {

	float x2, y2;
		int a2, b2;

};
struct Vector3
 {

	 float x3, y3;
	 float a3;

 };

int main()
 {

	 struct Vector1 v1;
	 struct Vector2 v2;
	 struct Vector3 v3;
	
		 v1 = v2;
	 v2 = v3;
	 v1 = v3;
	

}

