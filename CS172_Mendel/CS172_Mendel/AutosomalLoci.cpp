#include <iostream>
#include <string>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

//vector <vector <char>> genotypes;
//vector <string> phenotypes;
//Subcase = 0, Case 1 complete dominace, case 2 incomplete dominace, case 3 codominance
AutosomalLoci::AutosomalLoci()
{
	class_type = 1;
	char dom = 'A';
	char recess = 'a';
	this->getGenotypes(dom, recess);
	this->setSubclass();
	name = "default";
	string domPheno = "red", recessPheno = "yellow";
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
}

AutosomalLoci::AutosomalLoci(int case_type, char dom, char recess)
{
	alleles[0] = dom;
	alleles[1] = recess;
	class_type = case_type;
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
	this->setSubclass();
}

void AutosomalLoci::getGenotypes(char dom, char recess)
{
	vector <char> homoDom = { dom, dom };
	vector <char> hetero = { dom, recess };
	vector <char> homoRecess = { recess, recess };
	genotypes.push_back(homoDom);
	genotypes.push_back(hetero);
	genotypes.push_back(homoRecess);

}

void AutosomalLoci::getPhenotypes()
{
	string domPheno = "", recessPheno = "", codomPheno = "", incompDomPheno = "", name = "";
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	cout << "What is the dominant allele phenotype? (Auto.cpp)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (Auto.cpp)" << endl;
	cin >> recessPheno;
	if (class_type == 1)
	{
		phenotypes.push_back(domPheno);
		phenotypes.push_back(domPheno);
		phenotypes.push_back(recessPheno);
	}
	else if (class_type == 2)
	{
		phenotypes.push_back(domPheno);
		cout << "What is the incomplete dominance phenotype?" << endl;
		cin >> incompDomPheno;
		phenotypes.push_back(incompDomPheno);
		phenotypes.push_back(recessPheno);
	}
	else if (class_type == 3)
	{
		codomPheno = domPheno + " & " + recessPheno;
		phenotypes.push_back(domPheno);
		phenotypes.push_back(codomPheno);
		phenotypes.push_back(recessPheno);
	}
}

void AutosomalLoci::setSubclass()
{
	subclass = 1;
}

string AutosomalLoci::getPhenotypeSearch(vector <char> searchGeno)
{
	int size = genotypes.size();
	string returnPheno = "";
	for (int i = 0; i < size; i++)
	{
		if (genotypes.at(i) == searchGeno)
		{
			returnPheno = phenotypes.at(i);
		}
		else
		{
			scramble(searchGeno);
			if (genotypes.at(i) == searchGeno)
			{
				returnPheno = phenotypes.at(i);
			}
		}
	}
	if (returnPheno == "")
	{
		returnPheno = "Error, no compatible genotype.";
	}
	return returnPheno;
}

void AutosomalLoci::scramble(vector <char> &searchGeno)
{
	char temp = searchGeno.at(0);
	searchGeno.at(0) = searchGeno.at(1);
	searchGeno.at(1) = temp;
}

vector<vector <char>> AutosomalLoci::getGenotypeSearch( string searchPheno)
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
	return returnGeno;
}

string AutosomalLoci::getName()
{
	return name;
}

int AutosomalLoci::getSubClass()
{
	return subclass;
}

vector <string> AutosomalLoci::getPhenotypesAll()
{
	return phenotypes;
}

vector <vector <char>> AutosomalLoci::getGenotypesAll()
{
	return genotypes;
}