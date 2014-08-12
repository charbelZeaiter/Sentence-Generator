/**
 * Provides the implementation of
 * the Definition class, which is really
 * nothing more than an ordered pair: a nonterminal
 * attached to a string.
 */ 
 
#include "definition.h"
#include "random.h"

/**
 * Helper Method Prototypes
 * -----------------------
 */
 vector<Production> createProductionsList(ifstream& infile);
 string trimString(string& aString);

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
		char tempString[500];
		infile.getline(tempString, 500, '\n');

		// Fill Definition object
		std::string myStringObj = tempString;
		this->nonterminal = "<"+trimString(myStringObj);
		
		std::cout << "(" << this->nonterminal << ")" << endl;

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

   	std::cout << "XXXXXXXXXXXXXXXXXX-startIndex: (" << startIndex << ") endIndex: (" << endIndex << ")" << endl;  
   	
   	// Generate a random index within range.
   	RandomGenerator myRandomGenerator;
   	int randomIndex = myRandomGenerator.getRandomInteger(startIndex, endIndex);

   	std::cout << "ZZZZZZZZZZZZZZZZZZ-randomIndex: (" << randomIndex << ")" << endl;

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
	std::vector<Production> myProductions;

	// Peek ahead 1 char in stream to make 
	// sure we isolate definitions. Looking for '}'.
	char c = (char) infile.peek();

	// While production border not reached, parse internals.
	while( c != '}' && infile.good())
	{	
		Production newProduction = Production(infile);

		myProductions.push_back(newProduction);

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
