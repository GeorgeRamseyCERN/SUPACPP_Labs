// HEllO WORLD GR 12/11/25

//#include <root>
#include <iostream> 

//declare variables globally:


double MagFinder(double x, double y){
	
	double VectorLength = sqrt(x*x + y*y); 
	return VectorLength;
}

int main(){
	
	//run magfinder
	printf("Enter two space separated numbers for x and y for a vector length calc\n");
	//entering two numbers
	double x;
	double y;
		
	std::cin >> x >> y;
	
	if (std::cin.fail()){
		double x = 7.5;
		double y = 3.4; 
		printf("Invalid input: Setting vector as standard values: %f, %f \n", x, y);
	
		double VectorLength = MagFinder(x, y);

	}

	else{double VectorLength = MagFinder(x, y);
	
		printf("Hello World!\n The vector length is: %f \n", VectorLength);
	}

	return 0;
}

