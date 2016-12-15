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
	//Loci of organism, for trait of interest
	AutosomalLoci ofTrait;
	//Sex of organism
	char sex;
	//Genotype of organism, must match the loci gentoypes
	vector <char> genotype;
	//Phenotype of organism, obtained with loci search methods
	string phenotype;
public:
	//Default constructor for organism
	Organism();
	//Constructor for organism with input of genotype, sex, and loci 
	Organism(char sex, char first, char second, AutosomalLoci ofTrait);
	//Getter for the sex of the organism
	char getSex();
	//Getter for phenotype of organism after it was obtained from the loci methods
	string getPheno();
	//Getter for genotype of organism
	vector <char> getGeno();
	//Method to get the name of the loci object stored
	string getOfTraitName();
	//Method to get the phenotype for a genotype from the loci
	string getTraitPhenotype(vector <char> search);
	//Getter for subcase for loci
	int getSubCase();
	//Get all phenotypes for loci object
	vector <string> getPhenoAllOfTrait();
	//Getter for all genotypes from trait
	vector <vector <char>> getGenoAllOfTrait();
};

#endif

