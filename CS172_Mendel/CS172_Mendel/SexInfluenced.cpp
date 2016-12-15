#include <iostream>
#include <vector>
#include <string>
#include "SexInfluenced.h"
using namespace std;

//No arg constructor for class
SexInfluenced::SexInfluenced()
{
	char dom = 'D';
	char recess = 'd';
	this->setSubclass();
	genotypes.clear();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
}

//Constructor for Sex Influenced Trait, with input of alleles and sex that the trait is dominant in
SexInfluenced::SexInfluenced(char dom, char recess, char sexDom)
{
	//Sets subclass
	this->setSubclass();
	//Clears out default genotypes
	genotypes.clear();
	//Sets all other variables
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
	this->sexDom = sexDom;
}


//Method to fill phenotype vector for this derived class
void SexInfluenced::getPhenotypes()
{
	//Declaring necessary variables
	string domPheno = "";
	string recessPheno = "";
	string name = "";
	//Getting trait name
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	//Getting phenotypes
	cout << "What is the dominant allele phenotype? (SexINf.cpp)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (SexInf.cpp)" << endl;
	cin >> recessPheno;
	phenotypes.clear();
	//Filling phentoype vector
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
	//Filling phenotype vector for non dominant sex
	phenotypesNonDom.push_back(recessPheno);
	phenotypesNonDom.push_back(recessPheno);
	phenotypesNonDom.push_back(domPheno);
}

//Sets subclass tracking number of derived class
void SexInfluenced::setSubclass()
{
	subclass = 2;
}

//Phenotype search by sex
string SexInfluenced::getPhenotypeSearch(vector <char> searchGeno, char sex)
{
	int size = 0;
	string returnPheno = "";
	//Finds if matches sex trait is dominant in, hten searches first three phenotypes
	if ( sex == sexDom)
	{
		size = 3;
		for (int i = 0; i < size; i++)
		{
			if (genotypes.at(i) == searchGeno)
			{
				returnPheno = phenotypes.at(i);
			}
		}
		if (returnPheno == "")
		{
			returnPheno = "Error, no compatible genotype.";
		}
	}
	//Otherwise, search last three phenotypes
	else
	{
		size = 6;
		for (int i = 3; i < size; i++)
		{
			if (genotypes.at(i) == searchGeno)
			{
				returnPheno = phenotypes.at(i);
			}
		}
		if (returnPheno == "")
		{
			returnPheno = "Error, no compatible genotype.";
		}
	}
	return returnPheno;
}

//Genotype search by sex
vector <vector <char>> SexInfluenced::getGenotypeSearchBySex(string searchPheno, char sex)
{
	//search first three phenotypes if the sex is the same as that the trait is dominant in
	vector<vector <char>> returnGeno;
	if (sex == sexDom)
	{
		int size = phenotypes.size();
		for (int i = 0; i < size; i++)
		{
			if (phenotypes.at(i) == searchPheno)
			{
				returnGeno.push_back(genotypes.at(i));
			}
		}
	}
	//search last three phenotypes if not the sex the trait is dominant in
	else
	{
		int size = phenotypesNonDom.size();
		for (int i = 0; i < size; i++)
		{
			if (phenotypesNonDom.at(i) == searchPheno)
			{
				returnGeno.push_back(genotypes.at(i));
			}
		}
	}
	if (returnGeno.size() == 0)
	{
		vector <char> ret = { 'n', 'o' };
		returnGeno.push_back(ret);
	}
	return returnGeno;
}

//Search for genotype without sex variable
vector <vector <char>> SexInfluenced::getGenotypeSearch(string phenoSearch)
{
	vector<vector <char>> returnGeno;
	int size = phenotypes.size();
	//Searches through entire phenotype vector
	for (int i = 0; i < size; i++)
	{
		if (phenotypes.at(i) == phenoSearch)
		{
			returnGeno.push_back(genotypes.at(i));
		}
	}
	size = phenotypesNonDom.size();
	for (int j = 0; j < size; j++)
	{
		if (phenotypesNonDom.at(j) == phenoSearch)
		{
			returnGeno.push_back(genotypes.at(j));
		}
	}
	//Default answer if no genotypes are found
	if (returnGeno.size() == 0)
	{
		vector <char> ret = { 'n', 'o' };
		returnGeno.push_back(ret);
	}
	return returnGeno;
}