// This constains custom functiosn for teh FileHandler to use
// GR - 12/11/25

#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <cmath>
#include <cstddef>  // for size_t

// Magnitude calculator
double CalcMagnitude(double x, double y) {
    return std::sqrt(x * x + y * y);
}

// Recursive x^y function
double RecursivePow(double x, double y) {
	//printf("y = %f\n",y);
	double y_int = std::round(y);
	//printf("x = %f, y_int = %f\n", x, y_int);
	if(y_int == 0) return 1.0;
    if(y_int == 1) return x;
	if(y_int < 0) return 1.0/RecursivePow(x,-y_int);
    
	// round y first
	if (y_int == std::round( y_int / 2.0 ) * 2 ) { //y_int is even
		double half = RecursivePow( x, y_int / 2.0 );
		return half * half;
	} 
	if (y_int != std::round( y_int / 2 ) * 2 ) { //y_int is odd
    	return x * RecursivePow( x, y_int - 1);
	}
	else return -1;
}
// Chi-squared calculator
double CalcChi2(double x, double y, double xerr, double yerr, double p, double q) {
    // Predicted y
    double y_pred = p * x + q;

    // chi2 formula assuming independent errors
    double chi2 = (y - y_pred) * (y - y_pred) / (yerr * yerr + p*p*xerr*xerr);
    return chi2;
}
//CalcPQ
struct PQ{
	double p;
	double q;
};

PQ CalcPQ(double nRows, double sumXY, double sumX, double sumY, double sumX2, double sumY2){
	double N = nRows + 1;
    double P = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
    double Q = (sumY - P * sumX) / N;
	return {P, Q};
}
		
#endif // CUSTOMFUNCTIONS_H

