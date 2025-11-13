/*
    This is a class that handles the reading and merging of multiple files together 
    i.e the data and the errors together, and outputs to a root file as thats what
	i'll be using in analysis, so good practice for me!
	GR - 12/11/2025
*/


#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "CustomFunctions.h"

struct Data_Row {
    double x;
    double y;
    double xerr;
    double yerr;
    double xPowy; 
    double Mag;
};

struct ReadResults {
	int nRows;
    double sumX;
    double sumY;
    double sumXY;
    double sumX2;
    double sumY2;
	double chi2;
};

class FileHandler{
    public:

    //Variables

    // ROOT things
    TFile* outFile;
    TTree* dataTree;

    // Control bools
    bool isConnected;
    bool isVerbose;
    bool outputMade;
    bool chi2;
	bool XtoY;
	bool Mag;
	bool chi_calculated;

    // List of files connected
    std::vector<std::string> files;

	// Single row for filling Tree
    Data_Row row;

    // Functions

    // Constructor / destructor
    FileHandler(){
        isConnected     = false;
        isVerbose       = false;
        outputMade      = false;
        chi2            = false;
        XtoY            = false;
		Mag				= false;
		chi_calculated  = false;
    }
    ~FileHandler(){
        dataTree->Write();
        outFile->Close();
    }

    void MakeOutputFile(char* outputFileName);
   // void OpenStream(char* dataPath);
    ReadResults  ReadAllFiles(const std::string& dataPath, int nPrintRows, double p, double q);
    void FillTree(double x, double y, double xerr, double yerr, double xPowy, double Mag);
    void ConnectToTree();
    void SetVerbose(   		 bool in = true ){ isVerbose	  = in; }
    void SetChi2( 			 bool in = true ){ chi2			  = in; }
	void SetXtoY( 			 bool in = true ){ XtoY			  = in; }
	void SetMag(             bool in = true ){ Mag            = in; }
	void SetChi_calculated(  bool in = true ){ chi_calculated = in; }
};


// Make output file
void FileHandler::MakeOutputFile(char* outputFileName){
    outFile    = new TFile(outputFileName, "RECREATE");
    dataTree   = new TTree("dataTree", "Data and error file txt file format");
    outputMade = true;
}


// Connect a TTree branches to a internal data
void FileHandler::ConnectToTree(){
    dataTree->Branch("x", &row.x);
    dataTree->Branch("y", &row.y);
    dataTree->Branch("xerr", &row.xerr);
    dataTree->Branch("yerr", &row.yerr);
    dataTree->Branch("xPowy", &row.xPowy);
	dataTree->Branch("Mag", &row.Mag);

    isConnected = true;
}


// Fill the tree
void FileHandler::FillTree(double x, double y, double xerr, double yerr, double xPowy, double Mag){
	//printf("filling tree with row!");
	// Copy data to struct
    row.x     = x;
    row.y     = y;
    row.xerr  = xerr;
    row.yerr  = yerr;
    row.xPowy = xPowy;
    row.Mag   = Mag;
    // If not connected then connect then fill, otherwise fill
    if(!isConnected) ConnectToTree();
    dataTree->Fill();
}

ReadResults FileHandler::ReadAllFiles(const std::string& dataPath, int nPrintRows, double p, double q) {
    std::string inputPath = dataPath + "/input2D_float.txt";
    std::string errorPath = dataPath + "/error2D_float.txt";

    std::ifstream dataFile(inputPath);
    std::ifstream errorFile(errorPath);
	
//	printf("Trying to open:\n  %s\n  %s\n", inputPath.c_str(), errorPath.c_str());
	if (!dataFile.is_open()) {
    	printf("Failed to open data file: %s\n", inputPath.c_str());
	}	
	if (!errorFile.is_open()) {
    	printf("Failed to open error file: %s\n", errorPath.c_str());
	}

    if (!dataFile.is_open() || !errorFile.is_open()) {
        printf("Could not open input or error files\n");
        return {-1, -1, -1, -1, -1, -1, -1};
    }

    double x, y, xerr, yerr;
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0, chi2 = 0;
    int nRows = 0;
std::string lineData, lineError;


	//printf("nPrintRows = %i\n", nPrintRows);
    while (std::getline(dataFile, lineData) && std::getline(errorFile,lineError)) {
	//	printf("In while loop");
		//skip header
		if (lineData.empty() || lineData[0] == 'x') continue; //safety for other formats 
		
		// annoyingly in csv format 
		char comma;
		std::istringstream issData(lineData);
		std::istringstream issError(lineError);
		
		if (!(issData >> x >> comma >> y)) continue;
    	if (!(issError >> xerr >> comma >> yerr)) continue;

        if (nRows < nPrintRows) {
			printf("Row %d: x = %.6f, y = %.6f, xerr = %.6f, yerr = %.6f\n", nRows, x, y, xerr, yerr);
        }
																	
        double magnitude = 0.0;
        double xPowy = 0.0;

        if (Mag) {
            magnitude = CalcMagnitude(x,y);
        }

        if (!chi_calculated) {
            sumX  += x;
            sumY  += y;
            sumXY += x * y;
            sumX2 += x * x;
            sumY2 += y * y;
        }

        
        if (XtoY) {
            xPowy = RecursivePow(x,y);
        }

        if (chi_calculated) {
            double x2 = CalcChi2(x, y, xerr, yerr, p, q);
		//	printf("\r x2 = %.6f", x2);
			chi2 += x2;
			fflush(stdout);
        }

        // Fill the TTree
        FillTree(x, y, xerr, yerr, xPowy, magnitude);
        nRows++;
    }

    if (!chi_calculated) {
		printf("chi_calculated false\n");
    	printf("sum x = %f, sum y = %f, sum xy = %f, sum x^2 = %f, sum y^2 = %f\n", sumX, sumY, sumXY, sumX2, sumY2);
	}

    dataFile.close();
    errorFile.close();
	if (chi_calculated){
		printf("Chi2 sqaured is %f\n", chi2);
}
    return { nRows, sumX, sumY, sumXY, sumX2, sumY2, chi2 };
}

#endif
                                     

