#include <iostream>
#include <vector>
#include <string>
#include "Organism.h"
using namespace std;

Organism::Organism()
{
	sex = 'F';
	this->ofTrait = AutosomalLoci();
	vector <char> genoBase = { 'a', 'a' };
	genotype = genoBase;
	phenotype = ofTrait.getPhenotypeSearch(genoBase);
}

Organism::Organism(char sex, char first, char second, AutosomalLoci  ofTrait)
{
	this->sex = sex;
	vector <char> genoBase = { first, second };
	genotype = genoBase;
	this->ofTrait = ofTrait;
	phenotype = ofTrait.getPhenotypeSearch(genoBase);
}

char Organism::getSex()
{
	return sex;
}

string Organism::getPheno()
{
	return phenotype;
}

vector <char> Organism::getGeno()
{
	return genotype;
}

string Organism::getOfTraitName()
{
	return ofTrait.getName();
}

string Organism::getTraitPhenotype(vector <char> search)
{
	return ofTrait.getPhenotypeSearch(search);
}

int Organism::getSubCase()
{
	return ofTrait.getSubClass();
}


vector <string> Organism::getPhenoAllOfTrait()
{
	return ofTrait.getPhenotypesAll();
}

vector <vector <char>> Organism::getGenoAllOfTrait()
{
	return ofTrait.getGenotypesAll();
}
