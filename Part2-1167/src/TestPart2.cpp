//============================================================================
//
//% Student Name 1: student1
//% Student 1 #: 123456781
//% Student 1 userid (email): stu1 (stu1@sfu.ca)
//
//% Student Name 2: student2
//% Student 2 #: 123456782
//% Student 2 userid (email): stu2 (stu2@sfu.ca)
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put ‘none’ if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put ‘none’)__
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in Test.cpp if you are submitting that file too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "<userid1>_<userid2>" (eg. stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit one or two files to courses.cs.sfu.ca
//
// Name        : Part1.cpp
// Description : Course Project Part 1 (Tokenizer)
// Original Version Copyright (c) 2016 Simon Fraser University
//============================================================================


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Course Project Part 2
#include <vector>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/join.hpp>

#include "Part1Tokenizer.hpp"
#include "tokenClassifier.hpp"

using namespace boost::algorithm;
using namespace ensc251;
using namespace std;

#ifndef ENSC251_CHECK_EQUAL
#define ENSC251_CHECKER(A, B) BOOST_CHECK(A == B)
#else
#define ENSC251_CHECKER(A, B) BOOST_CHECK_EQUAL(A, B)
#endif

void check(std::string input, vector<std::string> expectedTypes)
{
	istringstream code(input);
	std::stringstream::pos_type pos = code.tellg();
	std::vector<std::string> tokenValues = tokenizeCodeStrip(code);
	code.clear();code.seekg(pos);
	std::vector<ensc251::Token*> tokenObjects = tokenClassifier(code);

	for(unsigned int i =0;i<expectedTypes.size();i++)
	{
		std::string type = ensc251::demangle(typeid(*tokenObjects.at(i)).name());
		if(type==expectedTypes.at(i)) {
			if(type=="ensc251::numeric_const<int>")
			{
				ensc251::numeric_const<int> *intToken = dynamic_cast<ensc251::numeric_const<int> *>(tokenObjects.at(i));
				ENSC251_CHECKER(intToken->getValue(), atoi(tokenValues.at(i).c_str()));
			}
			else if(type=="ensc251::numeric_const<float>")
			{
				ensc251::numeric_const<float> *floatToken = dynamic_cast<ensc251::numeric_const<float> *>(tokenObjects.at(i));
				ENSC251_CHECKER(floatToken->getValue(), atof(tokenValues.at(i).c_str()));
			}
			else if(type=="ensc251::numeric_const<char>")
			{
				ensc251::numeric_const<char> *charToken = dynamic_cast<ensc251::numeric_const<char> *>(tokenObjects.at(i));
				ENSC251_CHECKER(charToken->getValue(), tokenValues.at(i).at(0));
			}
			else
			{
				ensc251::StringBasedToken *strToken = dynamic_cast<ensc251::StringBasedToken *>(tokenObjects.at(i));
				ENSC251_CHECKER(strToken->getStringValue(), tokenValues.at(i));
			}
		}
		else {
			std::cout << "For below failure, expected tokenValue: " << tokenValues.at(i) << std::endl;
			BOOST_CHECK_EQUAL(type, expectedTypes.at(i));
		}
	}
}

BOOST_AUTO_TEST_CASE( test1 ){
	// type_spec, id, assignment_operator, int_const, punctuator.
	std::string input= "int a = 2 ;";
	vector<std::string> expectedTypes = {"ensc251::type_spec","ensc251::id", "ensc251::assignment_operator","ensc251::numeric_const<int>","ensc251::punctuator"};
	check(input, expectedTypes);
}

BOOST_AUTO_TEST_CASE( test1b ){
	// type_spec, id, assignment_operator, char_const, punctuator.
	std::string input= "char c = 'c' ;";
	vector<std::string> expectedTypes = {"ensc251::type_spec","ensc251::id", "ensc251::assignment_operator","ensc251::numeric_const<char>","ensc251::punctuator"};
	check(input, expectedTypes);
}

BOOST_AUTO_TEST_CASE( test2 ){
	// id, assignment_operator, float_const, div_operator, int_const, punctuator.
	std::string input= "_fnumber += 10.5 % 5;";
	vector<std::string> expectedTypes = {"ensc251::id","ensc251::assignment_operator", "ensc251::numeric_const<float>","ensc251::div_operator","ensc251::numeric_const<int>", "ensc251::punctuator"};
	check(input, expectedTypes);
}
BOOST_AUTO_TEST_CASE( test3 ){
	// id, assignment_operator, int_const, conditional_operator, punctuator, int_const, punctuator.
	std::string input= "Int = 01 ? 10 : 20 ;";
	vector<std::string> expectedTypes = {"ensc251::id","ensc251::assignment_operator","ensc251::numeric_const<int>","ensc251::conditional_operator","ensc251::numeric_const<int>","ensc251::punctuator","ensc251::numeric_const<int>","ensc251::punctuator"};
	check(input, expectedTypes);
}

BOOST_AUTO_TEST_CASE( test4 ){
	// id, assignment_operator, int_const, punctuator.
	std::string input= "a <<= 2 ;";
	vector<std::string> expectedTypes = {"ensc251::id" , "ensc251::assignment_operator", "ensc251::numeric_const<int>","ensc251::punctuator",};
	check(input, expectedTypes);
}

BOOST_AUTO_TEST_CASE( test5 ){
	// type_spec, id, assignment_operator, float_const, additive_operator, punctuator, id, postfix_operator, punctuator, punctuator.
	std::string input= "float f = 39E-2 + ( _f ++ ) ;";
	vector<std::string> expectedTypes = {"ensc251::type_spec", "ensc251::id","ensc251::assignment_operator","ensc251::numeric_const<float>", "ensc251::additive_operator", "ensc251::punctuator", "ensc251::id", "ensc251::postfix_operator","ensc251::punctuator", "ensc251::punctuator"};
	check(input, expectedTypes);
}

BOOST_AUTO_TEST_CASE( test6 ){
	// punctuator, id, assignment_operator, int_const, shift_operator, int_const, punctuator, punctuator.
	std::string input= "shifted = 10 << 2 ;";
	vector<std::string> expectedTypes = {"ensc251::id", "ensc251::assignment_operator", "ensc251::numeric_const<int>", "ensc251::shift_operator", "ensc251::numeric_const<int>", "ensc251::punctuator"};
	check(input, expectedTypes);

}

BOOST_AUTO_TEST_CASE( test7 ){
	// type_spec, unary_operator, id, assignment_operator, std::string, punctuator.
	std::string input= "char* _str = \"Hello World\" ;";
	vector<std::string> expectedTypes = {"ensc251::type_spec","ensc251::unary_operator","ensc251::id", "ensc251::assignment_operator","ensc251::StringConstant","ensc251::punctuator"};
	check(input, expectedTypes);
}
