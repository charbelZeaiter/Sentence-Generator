/**
 * Provides the implementation of the Production class, which
 * is simply a wrapper for the sequence of items (where items are terminals
 * or nonterminals).  It also completes the implementation of the ifstream
 * constructor, which was really the only thing missing from the .h
 */

#include "production.h"
#include <sstream>

/**
 * Helper Method Prototypes
 * -----------------------
 */
string trimString(const string& aString);
void formatForPunctuation(string& aString);

/**
 * Constructor Implementation: Production
 * --------------------------------------
 * Constructor that initializes the Production based
 * on the content of a file.
 */

Production::Production(ifstream& infile)
{	
   	// Get Production line to parse.
   	const size_t MAX_CHAR_ARRAY_SIZE = 1000;
	char tempString[MAX_CHAR_ARRAY_SIZE];
	infile.getline(tempString, MAX_CHAR_ARRAY_SIZE, '\n');
	
	// Convert to string object for better manipulation.
	string rawStringObject = tempString;
	string trimmedString = trimString(rawStringObject);

	// Prepare punctuation.
	formatForPunctuation(trimmedString);
	
	// Turn string into a stream for word easy extraction.
	stringstream myStringStream(trimmedString);

	// Loop through; extract and store all words in vector.
	string temp;
	myStringStream >> temp;
	while(temp != ";")
	{
		this->phrases.push_back(temp);
		
		myStringStream >> temp;
	}

}

 /**
   * formatForPunctuation
   * ---------------------
   * Takes a string a prepares the punctuation to
   * be interprated as a standalone terminal
   * if there are any spaces around it. This 
   * allows non-termnals to have punctuation next to
   * them.
 */
void formatForPunctuation(string& aString)
{
	// find match positions
   	size_t matchPos = aString.find_first_of(".,?!:");
  	
   	// Search through string until end. add extra spaces where needed.
   	while(matchPos < aString.length()) {
   		
   		// Matches at beginning or end of string dont count according to the rules.
   		if(matchPos != 0 || matchPos != (aString.length()-1)) {

   			// Find appropriate cases.
   			if( (aString[matchPos-1] != ' ' && aString[matchPos-1] != '\t') && 
   				(aString[matchPos+1] == ' ' || aString[matchPos+1] == '\t')	)
			{
				aString.insert(matchPos, " ");
			}
			else if( (aString[matchPos+1] != ' ' && aString[matchPos+1] != '\t') && 
   				(aString[matchPos-1] == ' ' || aString[matchPos-1] == '\t')	)
			{
				aString.insert(matchPos+1, " ");
			}

   		}

   		matchPos = aString.find_first_of(".,?!:", matchPos+1);
   	}
}
