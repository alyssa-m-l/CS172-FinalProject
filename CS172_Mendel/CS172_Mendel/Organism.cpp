#include <iostream>
#include <vector>
#include <string>
#include "Organism.h"
using namespace std;

//Organism no argument constructor, creates a female recesssive default loci organism
Organism::Organism()
{
	sex = 'F';
	this->ofTrait = AutosomalLoci();
	vector <char> genoBase = { 'a', 'a' };
	genotype = genoBase;
	phenotype = ofTrait.getPhenotypeSearch(genoBase);
}

//Organism constructor, with input of sex, genotype, and loci of trait
Organism::Organism(char sex, char first, char second, AutosomalLoci  ofTrait)
{
	//Sets sex, genotype, trait
	this->sex = sex;
	vector <char> genoBase = { first, second };
	genotype = genoBase;
	this->ofTrait = ofTrait;
	//Get phenotpe of organism using genotype search method in loci
	phenotype = ofTrait.getPhenotypeSearch(genoBase);
}

//Returns sex of organism
char Organism::getSex()
{
	return sex;
}

//Getter for phenotype of organsim
string Organism::getPheno()
{
	return phenotype;
}

//Getter for genotype of organsim
vector <char> Organism::getGeno()
{
	return genotype;
}

//Getter for trait name
string Organism::getOfTraitName()
{
	return ofTrait.getName();
}

//Getter for phenotype usign search method from loci
string Organism::getTraitPhenotype(vector <char> search)
{
	return ofTrait.getPhenotypeSearch(search);
}

//Getter for subcase of loci
int Organism::getSubCase()
{
	return ofTrait.getSubClass();
}

//Getter for phenotypes of loci
vector <string> Organism::getPhenoAllOfTrait()
{
	return ofTrait.getPhenotypesAll();
}

//Getter for genotype of organsim
vector <vector <char>> Organism::getGenoAllOfTrait()
{
	return ofTrait.getGenotypesAll();
}
