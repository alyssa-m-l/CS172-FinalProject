#ifndef XLINKED_H
#define XLINKED_H
#include <iostream>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

//Derivec class for X chromosome loci
class XLinked : public AutosomalLoci
{
public:
	//No argument constuctor 
	XLinked();
	//Constructor with input of alleles for X locus
	XLinked(char dom, char recess);
	//Methods to set genotypes and phenotypes for all possible combinations for loci
	virtual void getGenotypes(char dom, char recess);
	virtual void getPhenotypes();
	//Method to set subclass
	virtual void setSubclass();
	//Methods to search for phenotypes and genotypes
	string getPhenotypeSearchBySex(vector <char> searchGeno, char sex);
	vector<vector <char>> getGenotypeSearchBySex(string searchPheno, char sex);
};

#endif
