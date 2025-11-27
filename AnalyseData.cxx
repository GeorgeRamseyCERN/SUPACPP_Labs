
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
        printf("Error: No input directory specified. Files found Automatically.\n Use '--in path/to/directory'\n Specify an output '--out path/to/output' \n Add options '--chi2', '--XtoY', '--mag' '--print No.' as desired");
        return 1;
    }
		
	if(outName == NULL && !fh.chi2 && !fh.XtoY && !fh.Mag){
		outName = (char *) "New.root";
	}
	if(outName == NULL && (fh.chi2 || fh.XtoY || fh.Mag)){
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
    //printf("Processing data in directory: %s\n", inputDir.c_str());
    ReadResults results = fh.ReadAllFiles(inputDir, 0, p, q); // print in second loop to get nRows first
    printf("Processed %d rows from data\n", results.nRows);
	printf("Loop A\n");	

	if (results.nRows < printNo && !fh.chi2){
		printf("More prints than rows, will only print first 5, Loop B\n");
		printNo = 5;
		ReadResults resultsChi = fh.ReadAllFiles(inputDir, printNo, p, q);
	}

    // If chi2 flag is set, recalc with chi_calculated = true
    if(fh.chi2){
    	fh.SetChi_calculated(true);
        printf("chi_calculated now true - Loop C\n");
		PQ param =  CalcPQ(results.nRows, results.sumXY, results.sumX, results.sumY, results.sumX2, results.sumY2); 
       	printf("For y = px+n LS fit:\n p = %.6f,\n q = %.6f,\n", param.p, param.q); 
        ReadResults resultsChi = fh.ReadAllFiles(inputDir, printNo, param.p, param.q);
    }
    
	return 0;	
}



//since requirement to print 5 iff asked to print more than nRows, this HAS to be done in a second loop with my method of opening the file row by row. You could add another loop to get nRows at the start of opening the file but then defining another loop anyway, so not really much better. Without this added, the loop would simply print all the data and nothing more without issue, so this inefficiency is a quirk of the assignment; if only --printN is called in this case, I have to call the chi2 loop to check the length and print, and prevent it from filling the tree and doing the other calculations again, so a bit of extra faff! The Loops are labeled with a print to show this behaviour. 	
