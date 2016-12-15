#ifndef CROSS_H
#define CROSS_H
#include <iostream>
#include <vector>
#include "Organism.h"
#include "XLinked.h"
#include "SexLimited.h"
#include "SexInfluenced.h"
using namespace std;

class Cross
{
private:
	//private member variables
	//Array for storage of p-values and chi-squared tables for the chi squared tests
	static double chiSquaredTable[2][9];
	static double pTable[9];
	//Array of two organisms for cross
	Organism parents[2];
	//Method for Punnett square creation for both output to the screen and file
	void punnettSquare(ostream & out);
	//Bool value for if the cross is possible or not
	bool possible;
	//vector for storage of progeny genotypes
	vector <vector <char>> progeny;
	//Vector storage of progeny phenotypes 
	vector <string> progenyPhenotypes;
	//Vector for count of different types of phenotypes to generate ratios for Punnett Squares
	vector <int> progenyRatioNumbers;
	//Corresponding vector for Ratio Numbers for phenotypes to match numbers for output with Punnett Squares
	vector <string> progenyRatioPhenotypes;
	//Variables for chi squared output
	//Degrees of freedom variable
	double degreesOfFreedom;
	//Chi squared variable calculated with entered observed progeny and calculated expected progeny given rations from the Punnett square method
	double chi_squared;
	//????????
	bool necessary;
	//Storage of observed progeny numbers
	vector <int> progenyObserved;
	//Method to reorder genotype of progeny for Punnett Square output
	void orderProg(vector <char> &input);
	//Bool value to indicate if it is a non base class cross
	bool callSpecial;
	//Bool value to indicate if the cross it maternal or not
	bool maternal;
	//Method to get phenotypes for the non base class crosses
	void getProgPheno(int i);
	//Method to fill ratio vectors for Punnett Square output
	void fillRatios();
	//Method to call punnettSquare for output
	void punnettSquareToConsole();
	//Method to get observed progeny numbers, and calculate degrees of freedom and chisquared values
	void chiSquared();
	//add all necessary for output. File is not workign with combined input/output stuff.
public:
	//Consctructor for all crosses, with first inputted organism being female and the second being male
	Cross(Organism first, Organism second);
	//Method to carry out a maternal cross given already carried out cross
	void maternalCross();
	//I/O with punnett and chi squared values
	void printAll(string filename);
};

#endif

