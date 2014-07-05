struct Vector
{

	float x, y;

};
float dotMultiply(struct Vector pv1 );
float getX();
 float dotMultiply(struct Vector pdv1, struct Vector pdv2)
	{

		return pdv1.x*pdv2.y-pdv1.y*pdv2.x;

	}
 int main()
	 {

		 float a[10], c[10], b[10], d[10];
		 int i = 0;
		 struct Vector v1;
		 struct Vector v2;
		 while(i<10)
			 {

				 v1.x = a[i];
				 v1.y = b[i];
				 v2.x = c[i];
				 v2.y = d[i];
				 i = i+1;

			}
			return 0;

	}

