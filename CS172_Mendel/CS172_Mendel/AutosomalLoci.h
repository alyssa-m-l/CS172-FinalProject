#ifndef AUTOSOMALLOCI_H
#define AUTOSOMALLOCI_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Base Class for all Loci and Loci types
class AutosomalLoci
{
protected:
	//private member variables
	//Name of trait
	string name;
	//Identifier for subclass type
	int subclass;
	int class_type;
	//Array to store both alleles at the loci 
	char alleles[2];
	//Vector to store vectors containing the two allele combinations for all genotypes
	vector <vector <char>> genotypes;
	//Vector of all possible phenotypes matching the location of the the corresponding genotypes in the genotype vectors
	vector <string> phenotypes;
public:
	//Methods for class
	//Default constructor for base class
	AutosomalLoci();
	//Constuctor for input of alleles and type of dominance
	AutosomalLoci(int case_type, char dom, char recess);
	virtual void getGenotypes(char dom, char recess);
	//Method to set phenotypes with user input
	virtual void getPhenotypes();
	//Sets subclass
	virtual void setSubclass();
	//Finds and returns the first genotype which matches a given phenotype
	virtual string getPhenotypeSearch(vector <char> searchGeno);
	//Method to return the phenotype which matches a given genotype
	virtual vector<vector <char>> getGenotypeSearch( string searchPheno);
	//Method to return the name of a given trait
	string getName();
	//Method for getting the inheritance type for the base class
	int getSubClass();
	//Getter methods for all phenoytpes and genotypes of the trait
	vector <string> getPhenotypesAll();
	vector <vector <char>> getGenotypesAll();
	//Genotype search which reorders vector to assist with genotype based search in returning phenotypes
	void scramble(vector <char> &searchGeno);
};

#endif
