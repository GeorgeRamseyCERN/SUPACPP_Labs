// a script that calls the constructor for each InheritorClass.h class, claculates the integral over a sensible number of sampling points, prints range, chosen parameteres etc. and produces a plot of the fucntion. Also runs the Metrolpolis algorthim for generating new data 
// GR 14/11/25

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "CustomFunctions.h"
#include "FiniteFunctions.h"

int main() {

	FiniteFunction ff;

    // Read mystery data
    std::ifstream infile("../../Data/MysteryData20000.txt");
    std::vector<double> data;
    double val;
    while (infile >> val) data.push_back(val);

    double minval = *std::min_element(data.begin(), data.end());
    double maxval = *std::max_element(data.begin(), data.end());

    // Normal function - inputs are mean, sigma - seems to fit the data the best
    NormalFunction normal(-2.0,1.0);
    normal.setRangeMin(minval); normal.setRangeMax(maxval);
	normal.setOutfile("normal_output");
    normal.plotData(data,50,true);
	
	// sample wit metrolpolis
    int Nsamples = 5000;
	double width = 1; // smaller width is worse plot 
	std::vector<double> sampled = normal.metropolisSample(Nsamples, width);
	normal.plotData(sampled, 50, false); //false this time gives blue points 
	
	normal.plotFunction();
    normal.printInfo();

    // Cauchy-Lorentz function - inputs are x_0 and gamma
    CauchyFunction cauchy(-2,1.0);
    cauchy.setRangeMin(minval); cauchy.setRangeMax(maxval);
	cauchy.setOutfile("cauchy_output");
    cauchy.plotData(data,50,true);
    cauchy.plotFunction();
    cauchy.printInfo();

    // Crystal Ball function - inputs are alpha, n, mu, sigma
    CrystalBallFunction cb(1.5,2.0,-2.0,1.0);
    cb.setRangeMin(minval); cb.setRangeMax(maxval);
	cb.setOutfile("crystal_output");
    cb.plotData(data,50,true);
    cb.plotFunction();
    cb.printInfo();

	// still plot origianl example
	ff.setRangeMin(minval);
	ff.setRangeMax(maxval);	
	ff.plotData(data,50,true);
	printf("Plotted data\n");	
	ff.plotFunction();
	printf("Plotted all functions\n");	
    return 0;
}

 
