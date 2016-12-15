#ifndef SEXINFLUENCED_H
#define SEXINFLUENCED_H
#include <iostream>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

//Derived class Sex Influenced inheritance patterns for a autosomal loci
class SexInfluenced : public AutosomalLoci
{
private:
	//Character for sex in which the trait dominancy relationship is the same as the loci class dominancy arrangement
	char sexDom;
	//Vector for storage of other sex phenotypes
	vector <string> phenotypesNonDom;
public:
	//Default constructor
	SexInfluenced();
	//Constructor with inputs for genotypes and sex with typical dominancy relationship
	SexInfluenced(char dom, char recess, char sexDom);
	//Method for setting phenotypes
	virtual void getPhenotypes();
	//Method for setting subclass
	virtual void setSubclass();
	//Search methods for class
	virtual string getPhenotypeSearch(vector <char> searchGeno, char sex);
	virtual vector<vector <char>> getGenotypeSearch(string searchPheno);
	vector< vector <char>> getGenotypeSearchBySex(string searchPheno, char sex);
};

#endif
