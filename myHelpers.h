/*
 *  Contains all my custom helper declarations.
 **********************************************************/

#include "production.h"
#include <vector>

 /**
 * Helper Method: createProductionsList
 * ---------------------------
 * Returns a const reference to a list of
 * productions objects using a vector.
 */
 vector<Production> createProductionsList(ifstream& infile);
 
/**
 * Helper Method: trimString
 * ---------------------------
 * Returns a trimmed string version
 * of the input string.
 */
 string trimString(string& aString);