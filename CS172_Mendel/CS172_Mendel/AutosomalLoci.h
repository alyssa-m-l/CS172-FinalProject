#ifndef AUTOSOMALLOCI_H
#define AUTOSOMALLOCI_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class AutosomalLoci
{
protected:
	string name;
	int subclass;
	int class_type;
	char alleles[2];
	vector <vector <char>> genotypes;
	vector <string> phenotypes;
public:
	AutosomalLoci();
	AutosomalLoci(int case_type, char dom, char recess);
	virtual void getGenotypes(char dom, char recess);
	virtual void getPhenotypes();
	virtual void setSubclass();
	virtual string getPhenotypeSearch(vector <char> searchGeno);
	virtual vector<vector <char>> getGenotypeSearch( string searchPheno);
	string getName();
	int getSubClass();
	vector <string> getPhenotypesAll();
	vector <vector <char>> getGenotypesAll();
	void scramble(vector <char> &searchGeno);
};

#endif
