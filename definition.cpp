/**
 * Provides the implementation of
 * the Definition class, which is really
 * nothing more than an ordered pair: a nonterminal
 * attached to a string.
 */ 
 
#include "definition.h"
#include "random.h"
#include <limits>

/**
 * Helper Method Prototypes
 * -----------------------
 */
 vector<Production> createProductionsList(ifstream& infile);
 string trimString(const string& aString);

/**
 * Constructor: Definition
 * -----------------------
 * Constructs an instance of a Definition object
 * based on the content of the specified file.
 */

Definition::Definition(ifstream& infile)
{	
	// Peek ahead 1 char in stream to make 
	// sure we isolate definitions. Looking for '}'.
	char c = (char) infile.peek();
	
	// While definition border not reached, parse internals.
	while( c != '}' && infile.good())
	{	
		// Get Non-terminal.
		const size_t MAX_CHAR_ARRAY_SIZE = 500;
		char tempString[MAX_CHAR_ARRAY_SIZE];
		infile.getline(tempString, MAX_CHAR_ARRAY_SIZE, '\n');

		// Fill Definition object
		string myStringObj = tempString;
		this->nonterminal = "<"+trimString(myStringObj);

		// Create productions list.
		this->possibleExpansions = createProductionsList(infile);

		// Update Peek next char.
		c = (char) infile.peek();
	}
}

/**
 * Method: getRandomProduction
 * ---------------------------
 * Returns a const reference to one of the
 * embedded Productions.
 */

const Production& Definition::getRandomProduction() const
{
	// Index range.
	int startIndex = 0;
   	int endIndex = this->possibleExpansions.size()-1;

   	// Generate a random index within range using a fixed duration object.
   	static RandomGenerator myRandomGenerator;
   	int randomIndex = myRandomGenerator.getRandomInteger(startIndex, endIndex);

   	return this->possibleExpansions[randomIndex];
}

/**
 * Helper Method: createProductionsList
 * ---------------------------
 * Returns a const reference to a list of
 * productions objects using a vector.
 */

vector<Production> createProductionsList(ifstream& infile)
{
   	// Create vector list.
	vector<Production> myProductions;

	// Peek ahead 1 char in stream to make 
	// sure we isolate definitions. Looking for '}'.
	char c = infile.peek();

	// While production border not reached, parse internals.
	while( c != '}' && infile.good())
	{	
		// Check for rubbish char.
		if(c == '\n' || c == ' ' || c == '\t')
		{	
			// Ignore char.
	      	infile.ignore(numeric_limits<streamsize>::max(), c);
		}
		else
		{
			Production newProduction = Production(infile);

			myProductions.push_back(newProduction);
		}

		// Update Peek next char.
		c = (char) infile.peek();
	}

  	return myProductions;
}

/**
 * Helper Method: trimString
 * ---------------------------
 * Returns a trimmed string version
 * of the input string.
 */

string trimString(const string& aString)
{	
	string trimmedString = aString;

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
