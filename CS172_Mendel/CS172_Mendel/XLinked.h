#ifndef XLINKED_H
#define XLINKED_H
#include <iostream>
#include <vector>
#include "AutosomalLoci.h"
using namespace std;

class XLinked : public AutosomalLoci
{
public:
	XLinked();
	XLinked(char dom, char recess);
	virtual void getGenotypes(char dom, char recess);
	virtual void getPhenotypes();
	virtual void setSubclass();
	string getPhenotypeSearchBySex(vector <char> searchGeno, char sex);
	vector<vector <char>> getGenotypeSearchBySex(string searchPheno, char sex);
};

#endif
