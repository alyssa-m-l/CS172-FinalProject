#ifndef ORGANISM_H
#define ORGANISM_H
#include <iostream>
#include <vector>
#include <string>
#include "AutosomalLoci.h"
using namespace std;

class Organism
{
private:
	AutosomalLoci ofTrait;
	char sex;
	vector <char> genotype;
	string phenotype;
public:
	Organism();
	Organism(char sex, char first, char second, AutosomalLoci ofTrait);
	char getSex();
	string getPheno();
	vector <char> getGeno();
	string getOfTraitName();
	string getTraitPhenotype(vector <char> search);
	int getSubCase();
	vector <string> getPhenoAllOfTrait();
	vector <vector <char>> getGenoAllOfTrait();
};

#endif

