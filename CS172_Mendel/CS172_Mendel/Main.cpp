#include <iostream>
#include <string>
#include <vector>
#include "AutosomalLoci.h"
#include "XLinked.h"
#include "SexLimited.h"
#include "SexInfluenced.h"
#include "Organism.h"
#include "Cross.h"
using namespace std;

int main()
{
	AutosomalLoci testX(1, 'B', 'b');
	Organism test('F', 'B', 'b', testX);
	Organism test2('M', 'B', 'b', testX);
	Cross tryCross(test2, test);
	return 0;
}