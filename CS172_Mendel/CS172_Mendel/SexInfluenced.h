#ifndef SEXINFLUENCED_H
#define SEXINFLUENCED_H
#include <iostream>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

class SexInfluenced : public AutosomalLoci
{
private:
	char sexDom;
	vector <string> phenotypesNonDom;
public:
	SexInfluenced();
	SexInfluenced(char dom, char recess, char sexDom);
	virtual void getPhenotypes();
	virtual void setSubclass();
	virtual string getPhenotypeSearch(vector <char> searchGeno, char sex);
	virtual vector<vector <char>> getGenotypeSearch(string searchPheno);
	vector< vector <char>> getGenotypeSearchBySex(string searchPheno, char sex);
};

#endif
