//============================================================================
//
//% Student Name 1: Saeed Molaie
//% Student 1 #:301189698
//% Student 1 userid (email): smolaie@sfu.ca
//
//% Student Name 2: Gabe Teeger
//% Student 2 #: 301261001
//% Student 2 userid (email): gteeger@sfu.ca
//
// Helpers: Mohammad Akbari (TA)
// Name        : Part2.cpp
// Description : Course Project Part 2 (Token Classifier)

// ****NOTE: WE HAVE PLACED A DELETE OBJECT POINTER IN THE TESTPART2.CPP FILE
//           TO DELETE OBJECTS FROM HEAP AFTER WE ARE DONE USING THEM
//============================================================================
#include <vector>
#include <sstream>
#include <algorithm>
#include "tokenClasses.hpp"
#include "Part1Tokenizer.hpp"

using namespace std;
using namespace ensc251;

bool Check_is_punctuator(std::string token);
bool Check_is_type_spec(std::string token);
bool Check_is_assignment_operator(std::string token);
bool Check_is_conditional_operator(std::string token);
bool Check_is_shift_operator(std::string token);
bool Check_is_additive_operator(std::string token);
bool Check_is_div_operator(std::string token);
bool Check_is_unary_operator(std::string token);
bool Check_is_postfix_operator(std::string token);
int Check_is_numeric_const(std::string token);
bool Check_is_string_object(std::string token);
bool Check_is_incorrect_object(std::string token);

// Construct token objects categorized into appropriate types
// Input: a stream
// Output: a vector containing the list of Token objects properly categorized
std::vector<ensc251::Token*> tokenClassifier(istream& code)
{
		//Declaration of pointer objects and tokanization of code
        std::vector<ensc251::Token*> tokenObjectPs;
        std::vector<std::string> tokenValues1 = tokenizeCodeStrip(code); //put code stream into a vector of strings

        //Loop over tokanized string and classify them into objects
        for (unsigned int i=0; i< tokenValues1.size(); i++)
        {
        	if(Check_is_punctuator(tokenValues1[i]))
        	{
        		ensc251::punctuator punctuator_object(tokenValues1[i]);
        		tokenObjectPs.push_back(new ensc251::punctuator(punctuator_object));
        	}
        	else if(Check_is_type_spec(tokenValues1[i]))
        	{
        		ensc251::type_spec type_spec_object(tokenValues1[i]);
        		tokenObjectPs.push_back(new ensc251::type_spec(type_spec_object));
        	}
        	else if(Check_is_assignment_operator(tokenValues1[i]))
        	{
        		ensc251::assignment_operator assignment_operator_object(tokenValues1[i]);
        		tokenObjectPs.push_back(new ensc251::assignment_operator(assignment_operator_object));
        	}
        	else if(Check_is_conditional_operator(tokenValues1[i]))
        	{
        		ensc251::conditional_operator conditional_operator_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::conditional_operator(conditional_operator_object));
        	}
        	else if(Check_is_shift_operator(tokenValues1[i]))
        	{
        		ensc251::shift_operator shift_operator_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::shift_operator(shift_operator_object));
        	}
        	else if(Check_is_additive_operator(tokenValues1[i]))
        	{
        		ensc251::additive_operator additive_operator_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::additive_operator(additive_operator_object));
        	}
        	else if(Check_is_div_operator(tokenValues1[i]))
        	{
        		ensc251::div_operator div_operator_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::div_operator(div_operator_object));
        	}
        	else if(Check_is_unary_operator(tokenValues1[i]))
        	{
        		ensc251::unary_operator unary_operator_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::unary_operator(unary_operator_object));
        	}
        	else if(Check_is_postfix_operator(tokenValues1[i]))
        	{
        		ensc251::postfix_operator postfix_operator_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::postfix_operator(postfix_operator_object));
        	}
           	else if(Check_is_string_object(tokenValues1[i]))
			{
        		ensc251::string string_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::string(string_object));
			}
           	else if(Check_is_incorrect_object(tokenValues1[i]))
           	{
           	    ensc251::incorrect incorrect_object(tokenValues1[i]);
           	    tokenObjectPs.push_back(new ensc251::incorrect(incorrect_object));
            }
        	else if(Check_is_numeric_const(tokenValues1[i]) > 0)
			{
				if(Check_is_numeric_const(tokenValues1[i])==1)
				{
					numeric_const<int> numeric_const_int_object (std::atoi(tokenValues1[i].c_str()));
					tokenObjectPs.push_back(new ensc251::numeric_const<int>(numeric_const_int_object));
				}
				else if(Check_is_numeric_const(tokenValues1[i])==2)
				{
					ensc251::numeric_const<float> numeric_const_float_object(std::atof(tokenValues1[i].c_str()));
					tokenObjectPs.push_back(new ensc251::numeric_const<float>(numeric_const_float_object));
				}
				else if(Check_is_numeric_const(tokenValues1[i])==3)
				{
					ensc251::numeric_const<char> numeric_const_char_object(char(tokenValues1[i].at(1)));
					tokenObjectPs.push_back(new ensc251::numeric_const<char>(numeric_const_char_object));
				}
			}
        	else
        	{
        		ensc251::id id_object(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::id(id_object));
        	}
        }
        return tokenObjectPs;
}
bool Check_is_punctuator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
	std::string Token[]={";",":","{","}",")","(","*"};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_type_spec(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
	std::string Token[]={"char","int","float"};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_assignment_operator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
    std::string Token[]={"=","=+","=-","*=","/=","%=","<<=",">>=","&=","^=","|=","+="};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_conditional_operator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
    std::string Token[]={"?"};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_shift_operator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
    std::string Token[]={">>","<<"};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_additive_operator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
	std::string Token[]={"-","+"};;
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_div_operator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
	std::string Token[]={ "/" , "%"};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_unary_operator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
	std::string Token[]={"&" , "~"};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_postfix_operator(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;
	std::string Token[]={"++" , "--"};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);
	for(unsigned int i=0; i< sizeOftoken; i++)
	{
		if(Token[i]==token)
		{
			flag=1;
		}
	}
	return flag;
}
bool Check_is_string_object(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function. A zero is returned
//if the current string does not match any of the valid tokens.
{
	int flag=0;

	if(token[0]=='\"')
	{
		flag=1;
	}
	return flag;
}
bool Check_is_incorrect_object(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string matches
//any of the tokens defined in the function.
//Invalid tokens are returned as empty strings by the tokenizer.
//An empty string results in a one being returned.
//A zero is returned if the current string does not match any
//of the valid tokens.
{
	int flag=0;
	std::string Token[]={""};
	unsigned int sizeOftoken=sizeof(Token)/sizeof(Token[0]);

	for(unsigned int i=0; i< sizeOftoken; i++)
	{

		if(Token[i]==token)
		{

			cout<<"Error:  Token is invalid."<<endl;
			flag=1;
		}
	}
	return flag;
}
int Check_is_numeric_const(std::string token)
//Precondition: token is a single token that is currently being classified.
//Each token is an imported string from the various test-cases in Testpart2.cpp.
//Postcondition: A one is returned only if the current string is a
//numeric constant of type integer, a two is returned only if the current string
//is a numeric constant of type float, a three is returned only if the current string
//is a numeric constant of type char. A zero is returned if the current
//string does not match any of the valid tokens.
{
	int flag=0;
	const char *quote = "'";
	if(std::find_if(token.begin(), token.end(), (int(*)(int))std::isdigit) != token.end())
	{
		flag=1;
		if(		   token.find_first_of('.') != std::string::npos
				|| token.find_first_of('E') != std::string::npos
				|| token.find_first_of('e') != std::string::npos)
		{
			flag=2;
		}
	}
	else if(token[0] == *quote)
	{
		flag=3;
	}
	return flag;
}
