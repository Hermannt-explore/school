    #include <stdio.h>
    int main()
    {
   	float n;
 	float r;
	float x;
	x = 1;
	//scan for input
	scanf("%f %f", &n, &r);    
	
	while (r > 0){
		x = (x * (n/r));
	        n = n-1;
		r = r-1;	
	}
	printf("%f\n", x);         
    }
	
