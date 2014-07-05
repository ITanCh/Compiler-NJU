struct Vector
{

	float x, y;

};
float dotMultiply(struct Vector v1, struct Vector v2)
	 {

		float ret = v1.x*v2.y-v1.y*v2.x;
		
			return ret;
	

	}

 struct Vector2
 {

	float x1, y1;

 };
int main()
 {

	 float a[10], b, c[10];
	 float d[10];
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

