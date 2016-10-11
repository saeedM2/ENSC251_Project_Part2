//============================================================================
// Name        : Part2.cpp
// Description : Course Project Part 2 (Token Classifier)
//============================================================================

#include <vector>
#include <sstream>
#include <algorithm>
#include "tokenClasses.hpp"
#include "Part1Tokenizer.hpp"

using namespace std;
using namespace ensc251;

// Construct token objects categorized into appropriate types
// Input: a stream
// Output: a vector containing the list of Token objects properly categorized
std::vector<ensc251::Token*> tokenClassifier(istream& code)
{

        std::vector<ensc251::Token*> tokenObjectPs;

        //TODO: Write Code for classifying each token into respective classes
        // store the pointer to the object in tokenObjectPs vector.

        // the below line is likely wrong and will need to be updated

        std::vector<std::string> tokenValues1 = tokenizeCodeStrip(code); //put code stream into a vector of strings
        for (unsigned int i=0; i< tokenValues1.size(); i++)
        {
        	StringBasedToken Tokenized_string(tokenValues1[i]);

        	punctuator punctuator_variable(Tokenized_string.getStringValue( ));

        }

        tokenObjectPs.push_back(new ensc251::numeric_const<int>(1));

        return tokenObjectPs;
}

