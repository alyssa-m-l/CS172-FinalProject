#include <iostream>
#include <string>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

//vector <vector <char>> genotypes;
//vector <string> phenotypes;
//Subcase = 0, Case 1 complete dominace, case 2 incomplete dominace, case 3 codominance

//Default constructor for class, sets alleles to 'A' and 'a', simple dominance, color with red as dominant and yellow as recessive
AutosomalLoci::AutosomalLoci()
{
	class_type = 1;
	char dom = 'A';
	char recess = 'a';
	//Methods to fill all genotype combinations and set subclass
	this->getGenotypes(dom, recess);
	this->setSubclass();
	//Set all default values
	name = "default";
	string domPheno = "red", recessPheno = "yellow";
	//Fill phenotype vector
	phenotypes.push_back(domPheno);
	phenotypes.push_back(domPheno);
	phenotypes.push_back(recessPheno);
}

//Argument constructor
AutosomalLoci::AutosomalLoci(int case_type, char dom, char recess)
{
	//Fill allele array, dominant first, recessive second
	alleles[0] = dom;
	alleles[1] = recess;
	class_type = case_type;
	//Method to fill genotype and phenotype vectors, set subclass
	this->getGenotypes(dom, recess);
	this->getPhenotypes();
	this->setSubclass();
}

//Method to fill vector of vectors for genotypes
void AutosomalLoci::getGenotypes(char dom, char recess)
{
	//Creates vectors to be added to genotypes vector
	vector <char> homoDom = { dom, dom };
	vector <char> hetero = { dom, recess };
	vector <char> homoRecess = { recess, recess };
	//Push back all genotypes
	genotypes.push_back(homoDom);
	genotypes.push_back(hetero);
	genotypes.push_back(homoRecess);

}

//Method to fill phenotype vector
void AutosomalLoci::getPhenotypes()
{
	//Declaring string holders
	string domPheno = "", recessPheno = "", codomPheno = "", incompDomPheno = "", name = "";
	//Getting the name of the trait
	cout << "What is the trait name?" << endl;
	cin >> name;
	this->name = name;
	//Getting dominant and recessive phenotypes
	cout << "What is the dominant allele phenotype? (Auto.cpp)" << endl;
	cin >> domPheno;
	cout << "What is the recessive allele pehnotype? (Auto.cpp)" << endl;
	cin >> recessPheno;
	//Filling phenotype vectors depending on type of inheritance pattern (see top for key)
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

//Set subclass to keep track of base class and derived classes
void AutosomalLoci::setSubclass()
{
	subclass = 1;
}

//Method to find the phenotype for a given genotype
string AutosomalLoci::getPhenotypeSearch(vector <char> searchGeno)
{
	//Setting varaibles for searching through genotype vector
	int size = genotypes.size();
	string returnPheno = "";
	//Searching through genotype vector
	for (int i = 0; i < size; i++)
	{
		if (genotypes.at(i) == searchGeno)
		{
			returnPheno = phenotypes.at(i);
		}
		else
		{
			//Scrambles genotype vectors in case they are in a different order then that stored in the loci, and checks again
			scramble(searchGeno);
			if (genotypes.at(i) == searchGeno)
			{
				returnPheno = phenotypes.at(i);
			}
		}
	}
	//If a matching genotype is not found, returns default
	if (returnPheno == "")
	{
		returnPheno = "Error, no compatible genotype.";
	}
	return returnPheno;
}

//Method to reoder genotype for searching through genotype vector
void AutosomalLoci::scramble(vector <char> &searchGeno)
{
	char temp = searchGeno.at(0);
	searchGeno.at(0) = searchGeno.at(1);
	searchGeno.at(1) = temp;
}

//Method to find genotype for a given phenotype
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

//Getter for the name of the trait
string AutosomalLoci::getName()
{
	return name;
}

//Getter for stored subclass variable
int AutosomalLoci::getSubClass()
{
	return subclass;
}

//Getter for vector of all phenotypes of the trait
vector <string> AutosomalLoci::getPhenotypesAll()
{
	return phenotypes;
}

//Getter for vector of all possible genotypes of the trait
vector <vector <char>> AutosomalLoci::getGenotypesAll()
{
	return genotypes;
}