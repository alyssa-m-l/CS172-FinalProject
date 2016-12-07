#include <iostream>
#include <vector>
#include <string>
#include "SexLimited.h"
using namespace std;

SexLimited::SexLimited()
{
	expressed = 'F';
	char dom = 'C';
	char recess = 'c';
	this->setSubclass();
	this->getPhenotypes();
	this->getGenotypes(dom, recess);
}

SexLimited::SexLimited(char dom, char recess, char express)
{
	expressed = express;
	genotypes.clear();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
	this->setSubclass();
}

void SexLimited::getPhenotypes()
{
	string domPheno = "";
	string recessPheno = "";
	string name = "";
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	cout << "What is the dominant allele phenotype? (SexLim.cpp)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (SexLim.cpp)" << endl;
	cin >> recessPheno;
	phenotypes.clear();
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
	for (int i = 0; i < 3; i++)
	{
		nonExpressedPhenotypes.push_back(recessPheno);
	}
}

void SexLimited::setSubclass()
{
	subclass = 3;
}

string SexLimited::getPhenotypeSearch(vector <char> searchGeno, char sex)
{
	int size = 0;
	string returnPheno = "";
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

vector <vector <char>> SexLimited::getGenotypeSearch(string searchPheno)
{
	vector<vector <char>> returnGeno;
	int size = phenotypes.size();
	for (int i = 0; i < size; i++)
	{
		if (phenotypes.at(i) == searchPheno)
		{
			returnGeno.push_back(genotypes.at(i));
		}
	}
	size = nonExpressedPhenotypes.size();
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

vector<vector <char>> SexLimited::getGenotypeSearchBySex(string searchPheno, char sex)
{
	vector<vector <char>> returnGeno;
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