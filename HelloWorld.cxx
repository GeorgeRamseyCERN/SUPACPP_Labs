// HEllO WORLD GR 12/11/25

//#include <root>
#include <iostream> 

//declare variables globally:

double x = 7.5;
double y = 3.4; 

double MagFinder(){
	
	double VectorLength = sqrt(x**2 + y**2); 
	return VectorLength;
}

int main(){
	
	//run magfinder
	

	printf("Hello World!\n The vector length is: %d", VectorLength);
	return 0;
}

