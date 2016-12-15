#include <iostream>
#include <vector>
#include <string>
#include "Organism.h"
#include "Cross.h"
#include <fstream>
using namespace std;
// up to df = 2
//Stored chi squared and p-values for chi squared method
double Cross::pTable[9] = { 0.995, 0.975, 0.9, 0.5, 0.1, 0.05, 0.025, 0.01, 0.005 };
double Cross::chiSquaredTable[2][9] = { {0.000, 0.000, 0.016, 0.455, 2.706, 3.841, 5.024, 6.635, 7.7890}, {0.010, 0.051, 0.211, 1.386, 4.605, 5.991, 7.378, 9.210, 10.597} };
/*
Organism parents[2];
void punnettSquare();
bool possible;
vector <vector <char>> progeny;
vector <string> progenyPhenotypes;
*/

//Method to output punnett square to the console 
void Cross::punnettSquareToConsole()
{
	//passing cout as the ostream object for the method
	punnettSquare(cout);
}

//Method for creating punnett Square with the given stored ratio vectors
void Cross::punnettSquare(ostream & out)
{
	//Getting the stored genotypes of the parents 
	vector <char> father = parents[0].getGeno();
	vector <char> mother = parents[1].getGeno();
	//Getting all progeny genotypes stored, and ordering them
	vector <char> prog1 = progeny.at(0);
	orderProg(prog1);
	vector <char> prog2 = progeny.at(1);
	orderProg(prog2);
	vector <char> prog3 = progeny.at(2);
	orderProg(prog3);
	vector <char> prog4 = progeny.at(3);
	orderProg(prog4);
	//Outputting all gametes of the parents and the genotypes of the progeny
	out << "   " << father.at(0) << "    " << father.at(1) << endl;
	out << "__________________" << endl;
	out << mother.at(0) << "|" << " " << prog1.at(0) << prog1.at(1) << "|" << " " << prog2.at(0) << prog2.at(1) << "|" << endl;
	out << mother.at(1) << "|" << " " << prog3.at(0) << prog3.at(1) << "|" << " " <<  prog4.at(0) << prog4.at(1) << "|" << endl;
	out << "__________________" << endl;
	//Outputting ratios of all phenotypes
	int sizeOutPut = progenyRatioPhenotypes.size();
	if (maternal)
	{
		sizeOutPut = progenyRatioNumbers.size();
		maternal = false;
	}
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
		out << progenyRatioPhenotypes.at(i) << " " << progenyRatioNumbers.at(i) << " of " << total << endl;
	}
}


//Constructor for Cross object, with the input of the female, then the male parents
Cross::Cross(Organism first, Organism second)
{
	//Storing the parent organisms
	parents[0] = first;
	parents[1] = second;
	//Setting the initial condition to not carrying out a maternal cross
	maternal = false;
	possible = true;
	//Checking if the first organism is male
	if (first.getSex() == 'F')
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "First entered organsim must be male" << endl;
	}
	//Checking if the second organism is female
	if (second.getSex() == 'M')
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "Second entered organism must be female" << endl;
	}
	//Checking if the organisms have the same trait stored
	if (first.getOfTraitName() != second.getOfTraitName())
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "Organisms must be used for a monohybrid cross (Loci must be the same)." << endl;
		cout << "Organism one trait is: " << first.getOfTraitName() << endl;
		cout << "Organsim two trait is: " << second.getOfTraitName() << endl;
	}
	//Checking if the two organisms are of the same sex
	if (first.getSex() == second.getSex())
	{
		possible = false;
		cout << "Error!  Invalid cross!" << endl;
		cout << "Organisms must be of opposite sex.  Organism 1 is " << first.getSex() << " and organism 2 is " << second.getSex() << endl;
	}
	//If the cross is possible, and if it is, finding what subcase it falls under
	if (possible)
	{
		//If the cross is one of the derived classes, sets bool value to call the special progeny phenotype vector filling method to true
		if (first.getSubCase() != 1)
		{
			callSpecial = true;
		}
		else
		{
			callSpecial = false;
		}
	}
	//If the cross is not possible, creates default genotypes and phenotypes
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
	//If the cross is possible, fills genotypes for progeny
	else
	{
		//Declaring holder variables for parent genotypes
		vector <char> holder1 = first.getGeno();
		vector <char> holder2 = second.getGeno();
		// first org is father, second is mother
		vector <char> holder = { ' ', ' ' };
		//Filling genotype vector with progeny
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
		//If it is not a derived class, uses search methods to get phenotypes
		if (!callSpecial)
		{
			int size = progeny.size();
			for (int m = 0; m < size; m++)
			{
				progenyPhenotypes.push_back(first.getTraitPhenotype(progeny.at(m)));
			}
		}
		//If it is a derived class, calls the special phenotype setter method
		else
		{
			int call = first.getSubCase();
			getProgPheno(call);
		}
	}
	//Calls method to fill progeny ratio vectors
	this->fillRatios();
	//Outputs Punnett Square to console
	this->punnettSquareToConsole();
	//Uses chi squared method to fill chi squared variables for cross
	this->chiSquared();
}

//Method to carry out maternal trait cross, where the genotype of the mother determines the phenotypes of the children
void Cross::maternalCross()
{
	//Sets maternal condition to true
	maternal = true;
	int toFill = progenyPhenotypes.size();
	//second org is mother, getting genotype to find phenotype of all progeny
	vector <char> maternalGeno = parents[1].getGeno();
	progenyPhenotypes.clear();
	//Filling progeny phenotypes vector with maternal genotype's corresponding phenotype
	string progAll = parents[1].getTraitPhenotype(maternalGeno);
	for (int i = 0; i < toFill; i++)
	{
		progenyPhenotypes.push_back(progAll);
	}
	//Calls ratio filling methods, and outputs Punnett Square to console
	this->fillRatios();
	this->punnettSquareToConsole();
	//No chi squared necessary, as all progeny should have the same phenotype
	cout << "No chi-squared analysis necessary, all progeny will have the same phenotype." << endl;
}

//Method to fill all chi squared variables
void Cross::chiSquared()
{
	//Declaring variables to find the chi squared variables
	int types = progenyRatioPhenotypes.size();
	vector <double> observed;
	vector <double> expected;
	double holder = 0;
	double summation = 0;
	//Checking if a chi squared test is necessary, or if all stored phenotypes are the same
	necessary = false;
	for (int k = 0; k < types; k++)
	{
		if (progenyRatioPhenotypes.at(k) != progenyRatioPhenotypes.at(0))
		{
			necessary = true;
		}
	}
	//if a chi squared was necessary, does test
	if (necessary)
	{
		chi_squared = 0;
		for (int i = 0; i < types; i++)
		{
			//Prompts user to enter the number of each type of progeny observed
			cout << "Enter the number of " << progenyRatioPhenotypes.at(i) << " progeny: " << endl;
			cin >> holder;
			cout << progenyRatioPhenotypes.at(i) << " progeny: " << holder << endl;
			summation += holder;
			//Storing observed numbers
			observed.push_back(holder);
			progenyObserved.push_back(holder);
		}
		//Finds total size of progeny numbers
		double total = progeny.size();
		if (parents[0].getSubCase() == 3)
		{
			total = total * 2;
		}
		if (parents[0].getSubCase() == 2)
		{
			total = total * 2;
		}
		//Finding expected numbers of each type of phenotype given the ratio vectors
		for (int i = 0; i < progenyRatioPhenotypes.size(); i++)
		{
			holder = progenyRatioNumbers.at(i);
			expected.push_back((holder / total) * summation);
		}
		//Finding chi squared value
		for (int j = 0; j < observed.size(); j++)
		{
			holder = expected.at(j) - observed.at(j);
			chi_squared += (pow(holder, 2) / expected.at(j));
		}
		int findP = 0;
		cout << "Chi_squared is: " << chi_squared << endl;
		//Setting degrees of freedom
		degreesOfFreedom = progenyRatioPhenotypes.size() - 1;
		cout << "Degress of freedom are: " << degreesOfFreedom << endl;
		//Finding p value of cross
		for (int m = 0; m < 9; m++)
		{
			if (chi_squared > chiSquaredTable[progenyRatioPhenotypes.size() - 1][m])
			{
				findP = m;
			}
		}
		//Outputting p value range given table of chi squared and p values
		cout << "The p-value is between: " << pTable[findP] << " and " << pTable[findP + 1] << endl;
		//Outputting what the significance and the results of the cross are
		if (findP > 5)
		{
			cout << "The results are significant, and the predicted cross does not fit the results. " << endl;
		}
		else
		{
			cout << "The results fit the predicted values for the cross." << endl;
		}
	}
	//If no chi squared is necessary, as all phenotypes of the progeny are the same, outputs it
	else
	{
		cout << "All progeny should have the same phenotype, no chi squared analysis is necessary." << endl;
	}
}

//Method to order a genotype vector for nicer punnett square output
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

//Method nto fill progeny phenotype vector for derived classes
void Cross::getProgPheno(int i )
{
	//Clearing default constructor phenotypes
	progenyPhenotypes.clear();
	//Getting parent trait phenotypes to check against
	vector <string> allPhenOfTrait = parents[0].getPhenoAllOfTrait();
	vector <vector <char>> allGenoOfTrait = parents[0].getGenoAllOfTrait();
	//For Sex Influenced Traits, getting phenotypes
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
	//For Sex Limited traits, gets phenotypes of progeny
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
	//For X Linked traits, gets progeny phenotypes
	else if (i == 4)
	{
		int size = progeny.size();
		for (int m = 0; m < size; m++)
		{
			progenyPhenotypes.push_back(parents[0].getTraitPhenotype(progeny.at(m)));
		}
	}
}


//Method to fill ratio vectors for use in  Punnett Square methods
void Cross::fillRatios()
{
	//If not calling the maternal method, makes ratios
	int size = 0;
	if (!maternal)
	{
		//Setting initial phenotype and ratios
		progenyRatioPhenotypes.push_back(progenyPhenotypes.at(0));
		progenyRatioNumbers.push_back(1);
		//Getting number of progeny phenotypes to sort
		size = progenyPhenotypes.size();
		int temp = 0;
		//Declaring 'keys' to unlock different checks and filling sectiosn for the master for loop for ratio filling
		bool secondkey = false, thirdkey = false, firstSecond = false, firstThird = false;
		for (int i = 1; i < size; i++)
		{
			//If the phenotype matches the first phenotype, increases the ratio count
			if (progenyPhenotypes.at(i) == progenyRatioPhenotypes.at(0))
			{
				progenyRatioNumbers.at(0)++;
			}
			//Otherwise, it checks if the size of the array is one, and unlocks and initializes the second position
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
			//if it matches the second stored phenotype, increases it/ does nothing
			if (secondkey && progenyPhenotypes.at(i) == progenyRatioPhenotypes.at(1))
			{
				if (progenyPhenotypes.at(i) == progenyRatioPhenotypes.at(1))
				{
					//It is the first time through, sets first time to false
					if (firstSecond)
					{
						firstSecond = false;
					}
					//Increases ratio number
					else
					{
						progenyRatioNumbers.at(1)++;

					}
				}
			}
			else
			{
				//Opens and initializes third case if necessary
				if (parents[0].getSubCase() != 2 && progenyRatioPhenotypes.size() == 2)
				{
					progenyRatioPhenotypes.push_back(progenyPhenotypes.at(i));
					progenyRatioNumbers.push_back(1);
					firstThird = true;
					thirdkey = true;
				}
			}
			//If it matches the third case, opens this one
			if (thirdkey && progenyPhenotypes.at(i) == progenyPhenotypes.at(2))
			{
				if (progenyPhenotypes.at(i) == progenyPhenotypes.at(2))
				{
					//If first third, skips adding to ratio number
					if (firstThird)
					{
						firstThird = false;
					}
					//Adds one to the ratio number
					else
					{
						progenyRatioNumbers.at(2)++;
					}
				}
			}
		}
	}
	//If all phenotypes are the same, and the cross is maternal, adds four to the phenotype ratio vector
	else
	{
		progenyRatioNumbers.clear();
		progenyRatioNumbers.push_back(4);
	}
}


//Prints Punnett Square and Chi Squared values to file
void Cross::printAll(string filename)
{
	//Getting file name
	filename = filename + ".txt";
	//Opening file name
	ofstream file(filename);
	//Outputting header
	file << "Trait: " << parents[0].getOfTraitName() << endl;
	//Outputting punnett square
	punnettSquare(file);
	//If a chi squared is necessary, outputs all chi squared values
	if (necessary)
	{
		file << "Progeny observed: " << endl;
		for (int i = 0; i < progenyRatioPhenotypes.size(); i++)
		{
			file << progenyRatioPhenotypes.at(i) << " progeny: " << progenyObserved.at(i) << endl;
		}
		file << "Chi_squared is: " << chi_squared << endl;
		file << "Degress of freedom are: " << degreesOfFreedom << endl;
		int findP = 0;
		for (int m = 0; m < 9; m++)
		{
			if (chi_squared > chiSquaredTable[progenyRatioPhenotypes.size() - 1][m])
			{
				findP = m;
			}
		}
		file << "The p-value is between: " << pTable[findP] << " and " << pTable[findP + 1] << endl;
		if (findP > 5)
		{
			file << "The results are significant, and the predicted cross does not fit the results. " << endl;
		}
		else
		{
			file << "The results fit the predicted values for the cross." << endl;
		}
	}
	//else, outputs that chi squared is not necessary
	else
	{
		file << "All progeny should have the same phenotype, no chi squared analysis is necessary." << endl;
	}
	file.close();
}