#include <iostream>
#include <string>
#include <vector>
#include "XLinked.h"
using namespace std;

XLinked::XLinked()
{
	char dom = 'B';
	char recess = 'b';
	this->setSubclass();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
}

XLinked::XLinked(char dom, char recess)
{
	this->setSubclass();
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
}

void XLinked::getGenotypes(char dom, char recess)
{
	genotypes.clear();
	vector <char> homoDom = { dom, dom };
	vector <char> hetero = { dom, recess };
	vector <char> homoRecess = { recess, recess };
	vector <char> maleDom = { dom, 'Y' };
	vector <char> maleRecess = { recess, 'Y' };
	genotypes.push_back(homoDom);
	genotypes.push_back(hetero);
	genotypes.push_back(homoRecess);
	genotypes.push_back(maleDom);
	genotypes.push_back(maleRecess);
}

void XLinked::getPhenotypes()
{
	string domPheno = "";
	string recessPheno = "";
	string name = "";
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	cout << "What is the dominant allele phenotype? (XLinked)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (Xlinked)" << endl;
	cin >> recessPheno;
	phenotypes.clear();
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
}

void XLinked::setSubclass()
{
	subclass = 4;
}

string XLinked::getPhenotypeSearchBySex(vector <char> searchGeno, char sex)
{
	int size = 0;
	string returnPheno = "";
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

vector <vector <char>> XLinked::getGenotypeSearchBySex(string searchPheno, char sex)
{
	vector<vector <char>> returnGeno;
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