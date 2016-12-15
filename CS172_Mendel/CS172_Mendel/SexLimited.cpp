#include <iostream>
#include <vector>
#include <string>
#include "SexLimited.h"
using namespace std;

//No arg constructor for derived class
SexLimited::SexLimited()
{
	expressed = 'F';
	char dom = 'C';
	char recess = 'c';
	this->setSubclass();
	this->getPhenotypes();
	this->getGenotypes(dom, recess);
}

//Constructor for derived class
SexLimited::SexLimited(char dom, char recess, char express)
{
	//Sets sex that expresses the characteristic
	expressed = express;
	//Clears genotypes, then sets all variables
	genotypes.clear();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
	this->setSubclass();
}

//Sets phenotype vector
void SexLimited::getPhenotypes()
{
	//Declaring variables for filling vector
	string domPheno = "";
	string recessPheno = "";
	string name = "";
	//Gettng trait name
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	//Getting phenotypes
	cout << "What is the dominant allele phenotype? (SexLim.cpp)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (SexLim.cpp)" << endl;
	cin >> recessPheno;
	phenotypes.clear();
	//setting expressed phenotypes
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
	//setting all other phenotypes
	for (int i = 0; i < 3; i++)
	{
		nonExpressedPhenotypes.push_back(recessPheno);
	}
}

//Method to set subclass tracking number
void SexLimited::setSubclass()
{
	subclass = 3;
}

//Method to search by a genotype inside a given sex
string SexLimited::getPhenotypeSearch(vector <char> searchGeno, char sex)
{
	int size = 0;
	string returnPheno = "";
	//If the search sex matches the sex in which the trait is expressed, searches first three adresses
	if (sex == expressed)
	{
		size = phenotypes.size();
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
	else
	{
		returnPheno = nonExpressedPhenotypes.at(0);
	}
	return returnPheno;
}

//Method to get genotype from search phenotype
vector <vector <char>> SexLimited::getGenotypeSearch(string searchPheno)
{
	vector<vector <char>> returnGeno;
	int size = phenotypes.size();
	//Searches first vector 
	for (int i = 0; i < size; i++)
	{
		if (phenotypes.at(i) == searchPheno)
		{
			returnGeno.push_back(genotypes.at(i));
		}
	}
	size = nonExpressedPhenotypes.size();
	//Searches second vector
	for (int j = 0; j < size; j++)
	{
		if (nonExpressedPhenotypes.at(j) == searchPheno)
		{
			returnGeno.push_back(genotypes.at(j));
		}
	}
	if (returnGeno.size() == 0)
	{
		vector <char> ret = { 'n', 'o' };
		returnGeno.push_back(ret);
	}
	return returnGeno;
}

//Method to search for a given genotype by sex
vector<vector <char>> SexLimited::getGenotypeSearchBySex(string searchPheno, char sex)
{
	vector<vector <char>> returnGeno;
	//Searches first vector 
	if (sex == expressed)
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
	//Searches second vector
	else
	{
		int size = nonExpressedPhenotypes.size();
		for (int i = 0; i < size; i++)
		{
			if (nonExpressedPhenotypes.at(i) == searchPheno)
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