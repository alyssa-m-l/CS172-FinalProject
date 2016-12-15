#include <iostream>
#include <string>
#include <vector>
#include "AutosomalLoci.h"
#include "XLinked.h"
#include "SexLimited.h"
#include "SexInfluenced.h"
#include "Organism.h"
#include "Cross.h"
#include <fstream>
using namespace std;

//Test basic cross, and asks for output options

int main()
{
	//Note:  3 case types:
	//1 = simple dominance
	//2 = Codominance
	//3 = Incomplete dominance

	AutosomalLoci testX(1, 'B', 'b');
	Organism test('F', 'B', 'b', testX);
	Organism test2('M', 'B', 'b', testX);
	Cross tryCross(test2, test);
	string filename = "", response = "";
	cout << "Do you wish to export these results?" << endl;
	cin >> response;
	if (response == "yes" || response == "Yes")
	{
		cout << "Enter file name: " << endl;
		cin >> filename;
		tryCross.printAll(filename);
	}
	return 0;
}