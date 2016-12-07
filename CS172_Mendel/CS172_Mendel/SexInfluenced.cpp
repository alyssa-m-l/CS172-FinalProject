#include <iostream>
#include <vector>
#include <string>
#include "SexInfluenced.h"
using namespace std;

SexInfluenced::SexInfluenced()
{
	char dom = 'D';
	char recess = 'd';
	this->setSubclass();
	genotypes.clear();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
}

SexInfluenced::SexInfluenced(char dom, char recess, char sexDom)
{
	this->setSubclass();
	genotypes.clear();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
	this->sexDom = sexDom;
}

void SexInfluenced::getPhenotypes()
{
	string domPheno = "";
	string recessPheno = "";
	string name = "";
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	cout << "What is the dominant allele phenotype? (SexINf.cpp)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (SexInf.cpp)" << endl;
	cin >> recessPheno;
	phenotypes.clear();
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
	phenotypesNonDom.push_back(recessPheno);
	phenotypesNonDom.push_back(recessPheno);
	phenotypesNonDom.push_back(domPheno);
}

void SexInfluenced::setSubclass()
{
	subclass = 2;
}

string SexInfluenced::getPhenotypeSearch(vector <char> searchGeno, char sex)
{
	int size = 0;
	string returnPheno = "";
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

vector <vector <char>> SexInfluenced::getGenotypeSearchBySex(string searchPheno, char sex)
{
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

vector <vector <char>> SexInfluenced::getGenotypeSearch(string phenoSearch)
{
	vector<vector <char>> returnGeno;
	int size = phenotypes.size();
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
	if (returnGeno.size() == 0)
	{
		vector <char> ret = { 'n', 'o' };
		returnGeno.push_back(ret);
	}
	return returnGeno;
}