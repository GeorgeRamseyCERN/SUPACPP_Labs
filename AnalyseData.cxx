// Analyse Data - Assignment 1 GR 12/11/2025

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include "FileHandler.h"
#include "CustomFunctions.h"



//main
int main(int argc, char* argv[]){
	
	FileHandler fh;

	//set control bools 
	fh.SetVerbose(false);
	fh.SetMag(false);
	fh.SetXtoY(false);
	fh.SetChi2(false);
	fh.SetChi_calculated(false);

	std::string inputDir;
	std::vector<std::string> files;
	char* outName = NULL;
	int printNo = 0;
	double p = 0.0;
	double q = 0.0;

	for(int i = 0; i<argc; i++){
		if (strcmp(argv[i], "--in") == 0){
            inputDir = argv[++i];
        }
		if(strcmp (argv[i], "--out") == 0){
			outName = argv[++i];	
		}
		else if (strncmp(argv[i], "--print", 7) == 0) { // up to 7 digit no
        	const char* numberPart = argv[i] + 7;
        	if (*numberPart) {
            	printNo = atoi(numberPart); // convert to int
            	printf("Set printNo = %d\n", printNo);
			}
			else if (i +1 < argc ){ // version iwth space 
				printNo = atoi(argv[++i]);
            	printf("Set printNo = %d\n", printNo);
        	} else {
            	printf("Warning: '--print' flag used but no number specified, defaulting to 0\n");
        }
    }
		else if(strcmp (argv[i], "--chi2") == 0){
			fh.SetChi2(true);	
		}
		else if(strcmp (argv[i], "--XtoY") == 0){
			fh.SetXtoY(true);	
		}
		else if(strcmp (argv[i], "--mag") == 0){
            fh.SetMag(true);
        }
		
	}

	if (inputDir.empty()) {
        printf("Error: No input directory specified. Files found Automatically.\n Use '--in path/to/directory'\n");
        return 1;
    }

   /* if (files.size() == 0) {
        printf("No files specified. Use '+ input2D_float.txt + error2D_float.txt'\n");
        return 1;
    }*/
		
	if(outName == NULL && !fh.chi2 && !fh.XtoY && !fh.Mag){
		outName = (char *) "New.root";
	}
	if(outName == NULL && (fh.chi2 || fh.XtoY)){
		static char NameAdd[256] = "New";
        if(fh.chi2) strcat(NameAdd, "Chi2");
        if(fh.XtoY) strcat(NameAdd, "x^y");
		if(fh.Mag)  strcat(NameAdd, "Mag");
        strcat(NameAdd, ".root");
        outName = NameAdd;
		
	}

	printf("Output file: %s\n", outName);
	fh.MakeOutputFile(outName);

    // Loop over all input files
    printf("Processing data in directory: %s\n", inputDir.c_str());
    ReadResults results = fh.ReadAllFiles(inputDir, printNo, p, q); // read first 5 rows
    printf("Processed %d rows from data\n", results.nRows);

    // If chi2 flag is set, recalc with chi_calculated = true
    if(fh.chi2){
		printNo = 0;
    	fh.SetChi_calculated(true);
        printf("chi_calculated now true\n");
		PQ param =  CalcPQ(results.nRows, results.sumXY, results.sumX, results.sumY, results.sumX2, results.sumY2); 
       	printf("For y = px+n LS fit:\n p = %.6f,\n q = %.6f,\n", param.p, param.q); 
        ReadResults resultsChi = fh.ReadAllFiles(inputDir, printNo, param.p, param.q);
    }
    
	return 0;	
}



