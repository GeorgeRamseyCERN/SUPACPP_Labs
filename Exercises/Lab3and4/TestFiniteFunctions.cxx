// This script tests the defult version of FiniteFunctions Class
// GR 14/11/25
// it now also implements the pi calculator with metropolis

/*get fileinput from ../../Data/MysteryData20000.txt
produce a plot of this data - use plotData
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FiniteFunctions.h"


int main() {

	FiniteFunction ff;
	 	
    std::string filename = "../../Data/MysteryData20000.txt";
    std::ifstream infile(filename);
    
    if (!infile.is_open()) {
        printf("Error: could not open file.\n");
        return 1;
    }

    std::vector<double> data;
    double value;

    // Read all data points from the file
    while (infile >> value) {
        data.push_back(value);
    }
    infile.close();

    if (data.empty()) {
        printf("Error: no data found in file.\n");
        return 1;
    }

	ff.setOutfile("defaultFuncOutput_simsponsRuleInt");   // produces output.dat and output.png defined by class

	// Rmin and max values set at +/-5 and so out of range of data -> reset with setRangeMin/Max beyond default
	double minval = *std::min_element(data.begin(), data.end());
	double maxval = *std::max_element(data.begin(), data.end());

	ff.setRangeMin(minval);
	ff.setRangeMax(maxval);

	ff.plotData(data,50,true); // destructor creates plot png created at end of main
	printf("Plotted data\n");	
	ff.plotFunction();
	printf("Plotted function\n");	

	return 0;
}

