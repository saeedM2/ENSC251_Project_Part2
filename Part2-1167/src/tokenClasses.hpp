#ifndef TOKENCLASSES_HPP_
#define TOKENCLASSES_HPP_

#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;

namespace ensc251 {

		char *demangle(const char *typeName);

        class Token
        {
        	// The Base Token Class
        public:
         	 // we will fix this up when we learn about virtual functions.
			friend std::ostream& operator <<(std::ostream& outs, const Token& token)
			{
				token.print(outs);
				return outs;
			}

           virtual void print(std::ostream& str) const { str << demangle(typeid(*this).name()) << ": "; }

     	   virtual ~Token() {} // You will learn about virtual soon, but for now, don't delete this line.

		};

        class StringBasedToken:public Token {
			// subclasses: id, type_spec, assignment_operator, shift_operator, additive_operator, mul_operator, unary_operator, string
		private:
			std::string stringValue;

		public:
			//StringBasedToken() { std::cout << "Warning:  Do not invoke this constructor" << std::endl; }; // make sure this does not get invoked.
			StringBasedToken(const std::string &aStringValue) : stringValue("") {stringValue=aStringValue;}; // constructor
			const std::string& getStringValue( ) const { return stringValue;} // return the stringValue //getter function
			void print(std::ostream& str) const { Token::print(str); str << stringValue; }
        };

        class punctuator:public StringBasedToken
        {

        public:
			punctuator(std :: string value1):StringBasedToken(value1){}
        };

        class id:public StringBasedToken
        {
			// identifiers -- example:  sum
        public:
        	id(std :: string value1):StringBasedToken(value1){}
        };

        class type_spec:public StringBasedToken
		{
        public:
        	type_spec(std :: string value1):StringBasedToken(value1){}
		};

        class assignment_operator:public StringBasedToken
		{
        public:
        	assignment_operator(std :: string value1):StringBasedToken(value1){}
		};

        class conditional_operator:public StringBasedToken
		{
        public:
        	conditional_operator(std :: string value1):StringBasedToken(value1){}
		};

        class shift_operator:public StringBasedToken
		{
        public:
        	shift_operator(std :: string value1):StringBasedToken(value1){}
		};

        class additive_operator:public StringBasedToken
		{
        public:
        	additive_operator(std :: string value1):StringBasedToken(value1){}
		};

        class div_operator:public StringBasedToken
		{
        public:
        	div_operator(std :: string value1):StringBasedToken(value1){}
		};

        class unary_operator:public StringBasedToken
		{

        public:
        	unary_operator(std :: string value1):StringBasedToken(value1){}
		};

        class postfix_operator:public StringBasedToken
		{

        public:
        	 postfix_operator(std :: string value1):StringBasedToken(value1){}
		};

        class string:public StringBasedToken
        {
        public:
        	string(std :: string value1):StringBasedToken(value1){}
        };

        class incorrect:public StringBasedToken
		{
			// e.g., "sample string     --> This is incorrect ...
        	//		(quotation mark " is missing at the end)
		public:
			/* Fill in the implementation for constructor. Store a warning message */
        	incorrect(std :: string value1):StringBasedToken(value1){}
		};

        template<typename T> class numeric_const;

        class constant:public Token
		{
		};

        template<typename T>
        class numeric_const:public constant
		{
		private:
        	T value;
		public:
        	numeric_const(const T& constValue): value(constValue) {}
        	/*Fill in for additional constructors if desired */

        	const T& getValue() const {return value; }
        	void print(std::ostream& str) const {Token::print(str); str << ": " << value; }
		};

} // namespace ensc251

#endif /* PARSERCLASSES_HPP_ */
