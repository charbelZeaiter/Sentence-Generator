#include "myHelpers.h"

/**
 * Helper Method: createProductionsList
 * ---------------------------
 * Returns a const reference to a list of
 * productions objects using a vector.
 */

vector<Production> createProductionsList(ifstream& infile)
{
   	// Create vector list.
	std::vector<Production> myProductions;

	// Peek ahead 1 char in stream to make 
	// sure we isolate definitions. Looking for '}'.
	char c = (char) infile.peek();

	// While production border not reached, parse internals.
	while( c != '}' && infile.good())
	{	
		Production newProduction = Production(infile);

		//myProductions.push_back(newProduction);

		// Update Peek next char.
		c = (char) infile.peek();

		//std::cout << "Last peek: " << c << endl;
	}

  	return myProductions;
}

/**
 * Helper Method: trimString
 * ---------------------------
 * Returns a trimmed string version
 * of the input string.
 */

string trimString(string& aString)
{	
	std::string trimmedString = aString;

   	// Find true start position.
   	size_t startPos = aString.find_first_not_of(" \t\n");
   		
   	// Front trim if possible.
   	if(startPos != string::npos) {
   		trimmedString = trimmedString.substr(startPos);
   	}

   	// Find true end pos.
   	size_t endPos = aString.find_last_not_of(" \t\n");

   	// End trim if possible.
   	if(endPos != string::npos) {
   		trimmedString = trimmedString.substr(0, endPos+1);
   	}

  	return trimmedString;
}
