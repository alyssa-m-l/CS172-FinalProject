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
	//Need to add private vars vector <double> for progeny observed, vector <double> for expected, double for total offspring to do chi squared, p value, chi-squared value.....
	static double chiSquaredTable[2][9];
	static double pTable[9];
	Organism parents[2];
	void punnettSquare();
	bool possible;
	vector <vector <char>> progeny;
	vector <string> progenyPhenotypes;
	vector <int> progenyRatioNumbers;
	vector <string> progenyRatioPhenotypes;
	void orderProg(vector <char> &input);
	bool callSpecial;
	void getProgPheno(int i);
	void fillRatios();
public:
	Cross(Organism first, Organism second);
	void maternalCross(Organism first, Organism second);
	//I/O with punnett and chi squared values
	void chiSquared();
};

#endif

