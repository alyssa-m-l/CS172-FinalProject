#ifndef SEXLIMITED_H
#define SEXLIMITED_H
#include <iostream>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

class SexLimited : public AutosomalLoci
{
private:
	char expressed;
	vector <string> nonExpressedPhenotypes;
public:
	SexLimited();
	SexLimited(char dom, char recess, char express);
	virtual void getPhenotypes();
	virtual void setSubclass();
	virtual string getPhenotypeSearch(vector <char> searchGeno, char sex);
	virtual vector<vector <char>> getGenotypeSearch(string searchPheno);
	vector<vector <char>> getGenotypeSearchBySex(string searchPheno, char sex);
};

#endif

