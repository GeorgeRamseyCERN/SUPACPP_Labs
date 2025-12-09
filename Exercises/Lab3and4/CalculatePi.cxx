//Calculates pi using the metropolis algorithm 
//GR 09/12/25

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include "FiniteFunctions.h"

int main(int argc, char* argv[]) {

	FiniteFunction ff;
	
	// default values
    double radius = 1.0; 
    int nRandom = 10000; 
	bool DefaultValues = true;

    // parse command line arguments
    for(int i = 0; i < argc; i++){
        if (strcmp(argv[i], "--radius") == 0 && i + 1 < argc) {
            radius = atof(argv[++i]);
            printf("Set radius = %f\n", radius);
			DefaultValues = false;
        }
        else if (strcmp(argv[i], "--nRandom") == 0 && i + 1 < argc) {
            nRandom = atoi(argv[++i]);
            printf("Set nRandom = %d\n", nRandom);
			DefaultValues = false;
        }
    }
	if (DefaultValues){
		printf("No arguments passed, using defaults: --radius %f --nRandom %d\n", radius, nRandom);	
	}
    printf("Using radius: %f,  nRandom: %d\n", radius, nRandom); 
	
	// to generate pi: circle area pi r^2, square of same diamater is 2r^2 so ratio is pi/4. Generate points inside square and fraction falling inside circle approaches pi/4

	// Use Metropolis to generate independent x and y coords 
    
	double width = 0.5;
	ff.setRangeMin(0.0);
    ff.setRangeMax(1.0);
    std::vector<double> xSamples = ff.metropolisSample(nRandom, width);
    std::vector<double> ySamples = ff.metropolisSample(nRandom, width);

    // Shift and scale samples to [-radius, radius]
    for (auto &x : xSamples) x = (x - 0.5) * 2.0 * radius;
    for (auto &y : ySamples) y = (y - 0.5) * 2.0 * radius;

    // Count points inside the circle
    int inside = 0;
    for (int i = 0; i < nRandom; i++) {
        double x = xSamples[i];
        double y = ySamples[i];
        if (x*x + y*y <= radius*radius) inside++;
    }

    // Estimate pi
	double piEstimate = 4.0 * static_cast<double>(inside) / nRandom;
	printf("Estimated π = %.10f\n", piEstimate);

    return 0;
}

