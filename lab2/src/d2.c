struct Vector
 {
	float x, y;

};
float dotMultiply(struct Vector v1, struct Vector v2)
	 {

		float d = v1.x*v2.y-v1.y;
			return d;

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
				
					dotMultiply(v1, v2);
			}
		 return 0;
		

	}

