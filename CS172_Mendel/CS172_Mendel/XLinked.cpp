#include <iostream>
#include <string>
#include <vector>
#include "XLinked.h"
using namespace std;

//No arg constructor for loci 
XLinked::XLinked()
{
	char dom = 'B';
	char recess = 'b';
	this->setSubclass();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
}

//COnstructor for loci
XLinked::XLinked(char dom, char recess)
{
	//sets subclass, fills genotype and phenotype vector
	this->setSubclass();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
}

//Method to get all possible genotypes for the loci with inputted allele symbols
void XLinked::getGenotypes(char dom, char recess)
{
	genotypes.clear();
	//Declaring all possible genotypes
	vector <char> homoDom = { dom, dom };
	vector <char> hetero = { dom, recess };
	vector <char> homoRecess = { recess, recess };
	vector <char> maleDom = { dom, 'Y' };
	vector <char> maleRecess = { recess, 'Y' };
	//Adding all genotypes to genotype vector
	genotypes.push_back(homoDom);
	genotypes.push_back(hetero);
	genotypes.push_back(homoRecess);
	genotypes.push_back(maleDom);
	genotypes.push_back(maleRecess);
}

//Method to get all phenotypes, and add to phenotype vector
void XLinked::getPhenotypes()
{
	string domPheno = "";
	string recessPheno = "";
	string name = "";
	//Getting name of trait
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	//Getting dominant and recessive phenotypes
	cout << "What is the dominant allele phenotype? (XLinked)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (Xlinked)" << endl;
	cin >> recessPheno;
	phenotypes.clear();
	//Pushing phenotypes to vector in correct pattern
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
}

//Method to set subclass tracking number
void XLinked::setSubclass()
{
	subclass = 4;
}

//Method to search for a phenotype given a genotype by sex
string XLinked::getPhenotypeSearchBySex(vector <char> searchGeno, char sex)
{
	int size = 0;
	string returnPheno = "";
	//Searching first three positions
	if (sex == 'F')
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
	//Searching last two positions
	else
	{
		size = 5;
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

//Method to search for a genotype using a given phenotype by sex
vector <vector <char>> XLinked::getGenotypeSearchBySex(string searchPheno, char sex)
{
	vector<vector <char>> returnGeno;
	//Searching first three positions
	if (sex == 'F')
	{
		int size = 3;
		for (int i = 0; i < size; i++)
		{
			if (phenotypes.at(i) == searchPheno)
			{
				returnGeno.push_back(genotypes.at(i));
			}
		}
	}
	//Seaching last two positions
	else
	{
		int size = 5;
		for (int i = 3; i < size; i++)
		{
			if (phenotypes.at(i) == searchPheno)
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