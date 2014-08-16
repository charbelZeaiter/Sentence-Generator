/**
 * Provides the implementation of the full RSG application, which
 * relies on the services of the built-in string, ifstream, vector,
 * and map classes as well as the custom Production and Definition
 * classes provided with the assignment.
 */
 
#include <map>
#include <fstream>
#include <cstdlib>
#include <limits>
#include "definition.h"
#include "production.h"

using namespace std;

/**
 * Takes a reference to a legitimate infile (one that's been set up
 * to layer over a file) and populates the grammar map with the
 * collection of definitions that are spelled out in the referenced
 * file. 
 *
 * @param infile a valid reference to a flat text file storing the grammar.
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 */

  static void readGrammar(ifstream& infile, map<string, Definition>& grammar)
  {   
    // Keep parsing until EOF is reached.
    while(infile.good())
    { 
      // Ignore all chars until '{' is reached.
      infile.ignore(numeric_limits<streamsize>::max(), '{');

      // Ignore all chars until '\n' is reached.
      infile.ignore(numeric_limits<streamsize>::max(), '<');

      if(infile.good()) 
      {
        // Beginning of a definition; parse into program.
        Definition myDefinition = Definition(infile);
        
        // Fill map.
        string myNonTerminal = myDefinition.getNonterminal();
        pair<string, Definition> myPair(myNonTerminal, myDefinition);
        grammar.insert(myPair);
      }
    }

    infile.close();
}

/**
 * Takes in a non terminal and a result vector of strings 
 * and attempts to recursivly expand through till all words are
 * terminals. Modifying the vector.
 */
 
static void expandOn(const map<string, Definition>& grammar, int aNonTerminalPos, vector<string>& aResult)
{
    if(aNonTerminalPos == -1)
    {
      // Base case //
      
      return;
    }
    else
    { 
      // Recursive case //

      auto iterator = grammar.find(aResult[aNonTerminalPos]);

      // If non-terminal is not defined then display error msg and exit.
      if(iterator == grammar.end()) {
        cout << "Could not find \"" << aResult[aNonTerminalPos] << "\" in the grammar file." << endl;
        exit (EXIT_FAILURE);  
      }

      Definition myDefinition = iterator->second;

      Production myRandProduction = myDefinition.getRandomProduction();
      
      // Get iterator 1 passed pos to insert.
      auto resultIterator = aResult.begin()+aNonTerminalPos+1;
      aResult.insert(resultIterator, myRandProduction.begin(), myRandProduction.end());
      
      // Get new valid iterator and delete expanded non-terminal.
      resultIterator = aResult.begin()+aNonTerminalPos;
      aResult.erase(resultIterator);

      // Iterate through result vector to expand on non-terminals.
      // Start from previously expanded position.
      int newNonTerminalPos = -1;
      int pos = aNonTerminalPos;
      for(auto start = aResult.begin()+aNonTerminalPos; start != aResult.end(); start++)
      {
        // Check if non-terminal.
        if( (*start)[0] == '<')
        {
          newNonTerminalPos = pos;
          break;
        }
        pos++;
      }
      
      // Recurse.      
      expandOn(grammar, newNonTerminalPos, aResult);
    }
}

/**
 * Takes in a vector of terminals and combines
 * them to make one correctly formated string.
 */
string formatForOutput(const vector<string>& aResult)
{
  // String to store final combined output.
  string myString;

  // Loop through vector to append parts.
  for(auto start = aResult.crbegin(); start != aResult.crend(); start++)
  {
    if(start == aResult.crend()-1)
    {
      // Last insert.
      myString.insert(0, (*start) );
    }
    else if( (*start).find_first_of(".?:!,") != string::npos)
    {
      // If punctuation found.
      if((*start).find_first_not_of(".?:!,") != string::npos)
      {
        // Word includes punctuation.
        myString.insert(0, " "+(*start) );
      }
      else
      {
        // Isolated Punctuation found.
        myString.insert(0, (*start) );
      }
    }
    else
    {  
      // Not punctuation.
      myString.insert(0, " "+(*start) );
    }
  }

  return myString;
}

/**
 * Takes a const reference to a grammar stored in a map and prints
 * sentences produced by applying the grammar rules. The number of
 * sentences should be as specified by the second parameter.
 *
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 * @param numSentencesNeeded number of sentences to be produced
 */
 
static void generateRandomSentences(const map<string, Definition>& grammar, 
				    int numSentencesNeeded)
{
  
  // Loop through numSentencesNeeded times.
  int i;
  for(i=0;i<numSentencesNeeded;i++)
  {
    vector<string> myResult;

    myResult.push_back("<start>");
    
    // Randomly expand on a <start> non-terminal.
    expandOn(grammar, 0, myResult);
    
    // Prepare result to follow output rules.
    string output = formatForOutput(myResult);

    cout << output << endl;

    // Check that line is not last line.
    if(i != numSentencesNeeded-1)
    {
        cout << endl;
    } 

  }

}

/**
 * Performs the rudimentary error checking needed to confirm that
 * the client provided a grammar file.  It then continues to
 * open the file, read the grammar into a map<string, Definition>,
 * and then print out the random expansions as required.
 *
 * @param argc the number of tokens making up the command that invoked
 *             the RSG executable.  There must be at least two arguments,
 *             and only the first two are used.
 * @param argv the sequence of tokens making up the command, where each
 *             token is represented as a '\0'-terminated C string.
 */

int main(int argc, char *argv[])
{
  if (argc == 1) {
    cerr << "You need to specify the name of a grammar file." << endl;
    cerr << "Usage: rsg <path to grammar text file>" << endl;
    
    return EXIT_FAILURE;
  }
  
  ifstream grammarFile(argv[1]);
  if (grammarFile.fail()) {
    cerr << "Failed to open the file named \"" << argv[1] << "\". "
            "Check to ensure the file exists." << endl;
    return EXIT_FAILURE;
  }
  
  // things are looking good...
  map<string, Definition> grammar;
  readGrammar(grammarFile, grammar);
  generateRandomSentences(grammar, 3);
  
  return EXIT_SUCCESS;
}
