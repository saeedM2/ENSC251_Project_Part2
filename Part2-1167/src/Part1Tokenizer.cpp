/*
 * Part1Tokenizer.cpp
 *
 *  Created on: Oct 2, 2016
 *
 *  Copyright (c) 2016 School of Engineering Science, Simon Fraser University
 *
 *  ***** Interim version -- final version forthcoming *****
 */

#include "Part1Tokenizer.hpp"

// using namespace std;

#define WHITE "\n\r\t\v\f "

string delim3[] =  {">>=", "<<="};
string delim2[] =  {"+=","-=", "*=", "/=", "%=", ">>=", "<<=", "&=", "^=", "|=", "<<", ">>", ">=", "<=", "++", "--"};
string delim1andWhite =  WHITE "/()*%:;=&+-~!?";
string white = WHITE;

bool validateTokens(string token);
void processDigits(string line, unsigned long long &index);

// Accepts a stream and returns a vector of tokens with any remaining preprocessing directives stripped out
// Input: a stream
// Output: a vector of tokens
vector<string> tokenizeCodeStrip(istream& code) {

	// This is a solution based upon the May 26 Tutorial.
	vector<string> result;
	string line;
	bool invalidDigit=false;
	while (getline (code, line)) {
		if (line.at(0) == '#')
			continue;

		unsigned long long index2 = 0;
        unsigned long length = line.length();

		while(index2 != string::npos) {
			auto index1 = line.find_first_not_of(white, index2);
			if (index1 == string::npos)
				break;

			/// Dealing with int and float consts
			if ((line.at(index1) <= '9' && line.at(index1) >= '0') || line.at(index1) == '.')
			{
				index2 = index1;

				// integer consts
				processDigits(line, index2);

				// regular floats
				if (line.at(index2) == '.')
				{
					index2++;
					processDigits(line, index2);
				}

				// exponentials
				if (line.at(index2) == 'e' || line.at(index2) == 'E')
				{
					if(line.at(index2+1) == '+' || line.at(index2+1) == '-')
						index2+=2;
					else
						index2++;
					processDigits(line, index2);
				}

				// suffix f and F
				if (line.at(index2) == 'f' || line.at(index2) == 'F')
					index2++;

				auto subs = line.substr(index1, index2 - index1);
				result.push_back(subs);
				invalidDigit=true; // assume the digit is invalid until a delimeter is found!
				continue;
			}
			////

			// the below could go into a function.
			for (auto delim : delim3) {
				if (line.substr(index1, 3) == delim) {
					invalidDigit=false; // a delim is found so make the latest extracted digit valid.
					result.push_back(delim);
					index2 = index1 + 3;
					break;
				}
			}
			if (index2 > index1) continue;

			for (auto delim : delim2) {
				if (line.substr(index1, 2) == delim) {
					invalidDigit=false; // a delim is found so make the latest extracted digit valid.
					result.push_back(delim);
					index2 = index1 + 2;
					break;
				}
			}
			if (index2 > index1) continue;

			string size1String = line.substr(index1,1);
			if (size1String == "\"") {
				index2 = index1;
				while (index2 <= length) {
					index2++;
					if (line[index2] == '\\') {
						index2++; // skip over escaped character
					}
					else
						if (line[index2] == '\"') {
							index2++;
							result.push_back(line.substr(index1, index2 - index1));
							break;
						}
				}
			}
			if (index2 > length) { // String is not terminated!
				cout << "Error:  string is not terminated!" << endl;
				result.push_back("");
			}

			if (size1String == "'") {
				index2 = index1 + 1;
				if (line[index2] == '\\') {
					index2++; // skip over escaped character
				}
				index2++;
				if (line[index2] != '\'') // Character constant is not terminated!
				{
					cout << "Error:  character constant is not terminated!" << endl;
					result.push_back("");
				}
				else {
					index2++;
					result.push_back(line.substr(index1, index2 - index1));
				}
			}
			if (index2 > index1) continue;

			index2 = line.find_first_of(delim1andWhite, index1);
			if (index2 == index1){
				index2++; // we found a 1-character token delimiter
				invalidDigit=false; // a delim is found so make the latest extracted digit valid.
			}
			auto subs = line.substr(index1, index2 - index1);

			if(invalidDigit==true) // If the latest extracted digit is not valid, remove that (e.g., 12a in which no delim separating the numebr and the id, which results in an invalid id)
				result[result.size()-1] = "";
			else {
				if(validateTokens(subs)) // check for valid tokens (ids)
					result.push_back(subs);
				else
					result.push_back("");
			}
		}
	}
	return result;
}

bool validateTokens(string token)
{
	for (auto delim : delim2)
		if (token == delim)
			return true;

	for (auto delim : delim3)
		if (token == delim)
			return true;

	if(token.find_first_of(delim1andWhite, 0)!=string::npos)
		return true;

	if(token[0]=='_' || (token[0]>='a' && token[0]<='z') || (token[0]>='A' && token[0]<='Z'))
		for(unsigned int i=1;i<token.length();i++)
		{
			if(token[i]!='_' && !(token[i]>='a' && token[i]<='z') && !(token[i]>='A' && token[i]<='Z') && !(token[i]>='0' && token[i]<='9'))
				return false;
		}
	else
		return false;

	return true;
}

void processDigits(string line, unsigned long long &index)
{
	while (index < line.length() && line.at(index) <= '9' && line.at(index) >= '0')
		index++;
}



