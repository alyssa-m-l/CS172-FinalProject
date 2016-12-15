#ifndef SEXLIMITED_H
#define SEXLIMITED_H
#include <iostream>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

//Derived class for sex limited trait
class SexLimited : public AutosomalLoci
{
private:
	//Sex for trait which expresses the trait
	char expressed;
	//Vector of all recessive phenotypes for sex which does not express the trait
	vector <string> nonExpressedPhenotypes;
public:
	//No argument constructor
	SexLimited();
	//Constructor for object with input of genotype characters and sex which expresses the trait
	SexLimited(char dom, char recess, char express);
	//Method to set phenotypes for class for all genotypes
	virtual void getPhenotypes();
	//Method to set subclass for object
	virtual void setSubclass();
	//Search methods for loci to get genotypes and phenotypes
	virtual string getPhenotypeSearch(vector <char> searchGeno, char sex);
	virtual vector<vector <char>> getGenotypeSearch(string searchPheno);
	vector<vector <char>> getGenotypeSearchBySex(string searchPheno, char sex);
};

#endif

