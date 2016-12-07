#include <iostream>
#include <vector>
#include <string>
#include "Organism.h"
#include "Cross.h"
using namespace std;
// up to df = 2
double Cross::pTable[9] = { 0.995, 0.975, 0.9, 0.5, 0.1, 0.05, 0.025, 0.01, 0.005 };
double Cross::chiSquaredTable[2][9] = { {0.000, 0.000, 0.016, 0.455, 2.706, 3.841, 5.024, 6.635, 7.7890}, {0.010, 0.051, 0.211, 1.386, 4.605, 5.991, 7.378, 9.210, 10.597} };
/*
Organism parents[2];
void punnettSquare();
bool possible;
vector <vector <char>> progeny;
vector <string> progenyPhenotypes;
*/

void Cross::punnettSquare()
{
	vector <char> father = parents[0].getGeno();
	vector <char> mother = parents[1].getGeno();
	vector <char> prog1 = progeny.at(0);
	orderProg(prog1);
	vector <char> prog2 = progeny.at(1);
	orderProg(prog2);
	vector <char> prog3 = progeny.at(2);
	orderProg(prog3);
	vector <char> prog4 = progeny.at(3);
	orderProg(prog4);
	cout << "   " << father.at(0) << "    " << father.at(1) << endl;
	cout << "__________________" << endl;
	cout << mother.at(0) << "|" << " " << prog1.at(0) << prog1.at(1) << "|" << " " << prog2.at(0) << prog2.at(1) << "|" << endl;
	cout << mother.at(1) << "|" << " " << prog3.at(0) << prog3.at(1) << "|" << " " <<  prog4.at(0) << prog4.at(1) << "|" << endl;
	cout << "__________________" << endl;
	int sizeOutPut = progenyRatioPhenotypes.size();
	int total = progeny.size();
	if (parents[0].getSubCase() == 3)
	{
		total = total * 2;
	}
	if (parents[0].getSubCase() == 2)
	{
		total = total * 2;
	}
	for (int i = 0; i < sizeOutPut; i++)
	{
		cout << progenyRatioPhenotypes.at(i) << " " << progenyRatioNumbers.at(i) << " of " << total << endl;
	}
}

Cross::Cross(Organism first, Organism second)
{
	parents[0] = first;
	parents[1] = second;
	if (first.getSex() == 'F')
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "First entered organsim must be male" << endl;
	}
	if (second.getSex() == 'M')
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "Second entered organism must be female" << endl;
	}
	if (first.getOfTraitName() != second.getOfTraitName())
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "Organisms must be used for a monohybrid cross (Loci must be the same)." << endl;
		cout << "Organism one trait is: " << first.getOfTraitName() << endl;
		cout << "Organsim two trait is: " << second.getOfTraitName() << endl;
	}
	if (first.getSex() == second.getSex())
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "Organisms must be of opposite sex.  Organism 1 is " << first.getSex() << " and organism 2 is " << second.getSex() << endl;
	}
	if (possible)
	{
		if (first.getSubCase() != 1)
		{
			callSpecial = true;
		}
		else
		{
			callSpecial = false;
		}
	}
	if (!possible)
	{
		vector <char> blank = { ' ', ' ' };
		string phen = "N/A";
		possible = false;
		for (int i = 0; i < 4; i++)
		{
			progeny.push_back(blank);
			progenyPhenotypes.push_back(phen);
		}
	}
	else
	{
		possible = true;
		vector <char> holder1 = first.getGeno();
		vector <char> holder2 = second.getGeno();
		// first org is father, second is mother
		vector <char> holder = { ' ', ' ' };
		for (int j = 0; j < 2; j++)
		{
			holder.clear();
			for (int k = 0; k < 2; k++)
			{
				holder.push_back(holder1.at(k));
				holder.push_back(holder2.at(j));
				progeny.push_back(holder);
				holder.clear();
			}
		}
		if (!callSpecial)
		{
			int size = progeny.size();
			for (int m = 0; m < size; m++)
			{
				progenyPhenotypes.push_back(first.getTraitPhenotype(progeny.at(m)));
			}
		}
		else
		{
			this->getProgPheno(first.getSubCase());
		}
	}
	this->fillRatios();
	this->punnettSquare();
	this->chiSquared();
}

void Cross::maternalCross(Organism first, Organism second)
{
	int toFill = progenyPhenotypes.size();
	progenyPhenotypes.clear();
	//second org is mother
	vector <char> maternalGeno = second.getGeno();
	string progAll = second.getTraitPhenotype(maternalGeno);
	for (int i = 0; i < toFill; i++)
	{
		progenyPhenotypes.push_back(progAll);
	}
	this->fillRatios();
	this->punnettSquare();
	cout << "No chi-squared analysis necessary, all progeny will have the same phenotype." << endl;
}

void Cross::chiSquared()
{
	int types = progenyRatioPhenotypes.size();
	vector <double> observed;
	vector <double> expected;
	double holder = 0;
	double summation = 0;
	bool necessary = false;
	for (int k = 0; k < types; k++)
	{
		if (progenyRatioPhenotypes.at(k) != progenyRatioPhenotypes.at(0))
		{
			necessary = true;
		}
	}
	if (necessary)
	{
		for (int i = 0; i < types; i++)
		{
			cout << "Enter the number of " << progenyRatioPhenotypes.at(0) << " progeny: " << endl;
			cin >> holder;
			summation += holder;
			observed.push_back(holder);
		}
		double total = progeny.size();
		if (parents[0].getSubCase() == 3)
		{
			total = total * 2;
		}
		if (parents[0].getSubCase() == 2)
		{
			total = total * 2;
		}
		for (int i = 0; i < progenyRatioPhenotypes.size(); i++)
		{
			holder = progenyRatioNumbers.at(i);
			expected.push_back((holder / total) * summation);
		}
		double chi_squared = 0;
		for (int j = 0; j < observed.size(); j++)
		{
			holder = expected.at(j) - observed.at(j);
			chi_squared += (pow(holder, 2) / expected.at(j));
		}
		cout << "Chi_squared is: " << chi_squared << endl;
		cout << "Degress of freedom are: " << progenyRatioPhenotypes.size() - 1 << endl;
		int findP = 0;
		cout << "chi squared values: " << endl;
		bool notFound = true;
		for (int m = 0; m < 9; m++)
		{
			if (chi_squared > chiSquaredTable[progenyRatioPhenotypes.size() - 1][m] && notFound)
			{
				findP = m;
				notFound = false;
			}
		}
		cout << "The p-value is between: " << pTable[findP] << " and " << pTable[findP + 1] << endl;
		if (findP > 5)
		{
			cout << "The results are significant, and the predicted cross does not fit the results. " << endl;
		}
		else
		{
			cout << "The results fit the predicted values for the cross." << endl;
		}
	}
	else
	{
		cout << "All progeny should have the same phenotype, no chi squared analysis is necessary." << endl;
	}
}

void Cross::orderProg(vector <char> &input)
{
	int size = input.size();
	char storage;
	if (input.at(0) > input.at(1))
	{
		storage = input.at(0);
		input.at(0) = input.at(1);
		input.at(1) = storage;
	}
}

//now will call, just need way to get correct phenotypes in place for cases 2-4.
void Cross::getProgPheno(int i )
{
	//now have all into in a loci
	progenyPhenotypes.clear();
	vector <string> allPhenOfTrait = parents[0].getPhenoAllOfTrait();
	vector <vector <char>> allGenoOfTrait = parents[0].getGenoAllOfTrait();
	if (i == 2)
	{
		int size = progeny.size();
		for (int m = 0; m < size; m++)
		{
			progenyPhenotypes.push_back(parents[0].getTraitPhenotype(progeny.at(m)));
		}
		string holder = "";
		for (int m = 0; m < size; m++)
		{
			if (parents[0].getTraitPhenotype(progeny.at(m)) == allPhenOfTrait.at(0))
			{
				holder = allPhenOfTrait.at(2);
			}
			else if (parents[0].getTraitPhenotype(progeny.at(m)) == allPhenOfTrait.at(2))
			{
				holder = allPhenOfTrait.at(0);
			}
			progenyPhenotypes.push_back(holder);
		}
	}
	else if (i == 3)
	{
		int size = progeny.size();
		for (int m = 0; m < size; m++)
		{
			progenyPhenotypes.push_back(parents[0].getTraitPhenotype(progeny.at(m)));
		}
		for (int m = 0; m < size; m++)
		{
			progenyPhenotypes.push_back(allPhenOfTrait.at(2));
		}
	}
	else if (i == 4)
	{
		int size = progeny.size();
		for (int m = 0; m < size; m++)
		{
			progenyPhenotypes.push_back(parents[0].getTraitPhenotype(progeny.at(m)));
		}
	}
}



void Cross::fillRatios()
{
	progenyRatioPhenotypes.push_back(progenyPhenotypes.at(0));
	progenyRatioNumbers.push_back(1);
	int size = progenyPhenotypes.size();
	int temp = 0;
	bool secondkey = false, thirdkey = false, firstSecond = false, firstThird = false;
	for (int i = 1; i < size; i++)
	{
		if (progenyPhenotypes.at(i) == progenyRatioPhenotypes.at(0))
		{
			progenyRatioNumbers.at(0)++;
		}
		else
		{
			if (progenyRatioPhenotypes.size() == 1)
			{
				progenyRatioPhenotypes.push_back(progenyPhenotypes.at(i));
				progenyRatioNumbers.push_back(1);
				firstSecond = true;
				secondkey = true;
			}
		}
		if (secondkey)
		{
			if (progenyPhenotypes.at(i) == progenyRatioPhenotypes.at(1))
			{
				if (firstSecond)
				{
					firstSecond = false;
				}
				else
				{
					progenyRatioNumbers.at(1)++;
					
				}
			}
		}
		else
		{
			if (progenyRatioPhenotypes.size() == 2)
			{
				progenyRatioPhenotypes.push_back(progenyPhenotypes.at(i));
				progenyRatioNumbers.push_back(1);
				firstThird = true;
				thirdkey = true;
			}
		}
		if (thirdkey)
		{
			if (progenyPhenotypes.at(i) == progenyPhenotypes.at(2))
			{
				if (firstThird)
				{
					firstThird = false;
				}
				else
				{
					progenyRatioNumbers.at(2)++;
				}
			}
		}
	}
}