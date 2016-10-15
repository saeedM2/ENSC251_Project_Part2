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
//ensc251::assignment_operator_spec* assignment_operator_spec(std::string token);

// Construct token objects categorized into appropriate types
// Input: a stream
// Output: a vector containing the list of Token objects properly categorized
std::vector<ensc251::Token*> tokenClassifier(istream& code)
{

        std::vector<ensc251::Token*> tokenObjectPs;

        //TODO: Write Code for classifying each token into respective classes
        // store the pointer to the object in tokenObjectPs vector.
        // the below line is likely wrong and will need to be updated

        ensc251::punctuator* punctuator_object;
        ensc251::id* id_object;
        ensc251::type_spec* type_spec_object;
        ensc251::assignment_operator* assignment_operator_object;
        ensc251::conditional_operator* conditional_operator_object;
        ensc251::shift_operator* shift_operator_object;
        ensc251::additive_operator* additive_operator_object;
        ensc251::div_operator* div_operator_object;
        ensc251::unary_operator* unary_operator_object;
        ensc251::postfix_operator* postfix_operator_object;
        ensc251::string* string_object;
        ensc251::incorrect* incorrect_object;
        ensc251:: numeric_const<int>*numeric_const_int_object;
        ensc251:: numeric_const<float>*numeric_const_float_object;
        ensc251:: numeric_const<char>*numeric_const_char_object;

        int check_constant_type=0;

        std::vector<std::string> tokenValues1 = tokenizeCodeStrip(code); //put code stream into a vector of strings
        for (unsigned int i=0; i< tokenValues1.size(); i++)
        {
        	if(Check_is_punctuator(tokenValues1[i]))
        	{
        		punctuator_object=new punctuator(tokenValues1[i]);
        		tokenObjectPs.push_back(new ensc251::punctuator(*punctuator_object));
        	}
        	else if(Check_is_type_spec(tokenValues1[i]))
        	{
        		type_spec_object=new type_spec(tokenValues1[i]);
        		tokenObjectPs.push_back(new ensc251::type_spec(*type_spec_object));
        	}
        	else if(Check_is_assignment_operator(tokenValues1[i]))
        	{
        		assignment_operator_object=new assignment_operator(tokenValues1[i]);
        		tokenObjectPs.push_back(new ensc251::assignment_operator(*assignment_operator_object));
        	}
        	else if(Check_is_conditional_operator(tokenValues1[i]))
        	{
        		conditional_operator_object=new conditional_operator(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::conditional_operator(*conditional_operator_object));
        	}
        	else if(Check_is_shift_operator(tokenValues1[i]))
        	{
        		shift_operator_object=new shift_operator(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::shift_operator(*shift_operator_object));
        	}
        	else if(Check_is_additive_operator(tokenValues1[i]))
        	{
        		additive_operator_object=new additive_operator(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::additive_operator(*additive_operator_object));
        	}
        	else if(Check_is_div_operator(tokenValues1[i]))
        	{
        		div_operator_object=new div_operator(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::div_operator(*div_operator_object));
        	}
        	else if(Check_is_unary_operator(tokenValues1[i]))
        	{
        		unary_operator_object=new unary_operator(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::unary_operator(*unary_operator_object));
        	}
        	else if(Check_is_postfix_operator(tokenValues1[i]))
        	{
        		postfix_operator_object=new postfix_operator(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::postfix_operator(*postfix_operator_object));
        	}
           	else if(Check_is_string_object(tokenValues1[i]))
			{
				string_object=new ensc251::string(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::string(*string_object));
			}
        	else if(Check_is_numeric_const(tokenValues1[i]) > 0)
			{

        		check_constant_type=Check_is_numeric_const(tokenValues1[i]);
				if(check_constant_type==1)
				{
					numeric_const_int_object=new numeric_const<int>(std::atoi(tokenValues1[i].c_str()));
					tokenObjectPs.push_back(new ensc251::numeric_const<int>(*numeric_const_int_object));
				}
				else if(check_constant_type==2)
				{
					numeric_const_float_object=new numeric_const<float>(std::atof(tokenValues1[i].c_str()));
					tokenObjectPs.push_back(new ensc251::numeric_const<float>(*numeric_const_float_object));
				}
				else if(check_constant_type==3)
				{
					numeric_const_char_object=new numeric_const<char>(char(tokenValues1[i].at(1)));
					tokenObjectPs.push_back(new ensc251::numeric_const<char>(*numeric_const_char_object));
				}
			}
        	else
        	{
        		id_object=new id(tokenValues1[i]);
				tokenObjectPs.push_back(new ensc251::id(*id_object));
        	}
        }
/*
		std::cout<<endl;
		std::cout<<type_spec_object->getStringValue()<<endl;
		std::cout<<endl;

		cout<<endl;
        cout<<punctuator_object->getStringValue()<<endl;
        cout<<endl;
*/
        //tokenObjectPs.push_back(new ensc251::numeric_const<int>(1));

        for(unsigned int k=0; k < tokenObjectPs.size();k++ )
        {
        	cout<<endl;
        	cout<<*tokenObjectPs[k]<<endl;
        	cout<<endl;
        }
        return tokenObjectPs;
}
bool Check_is_punctuator(std::string token)
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
{
	int flag=0;

	if(token[0]=='\"')
	{
		flag=1;
	}
	return flag;
}
int Check_is_numeric_const(std::string token)
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
