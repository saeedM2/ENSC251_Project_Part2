#ifndef TOKENCLASSES_HPP_
#define TOKENCLASSES_HPP_

#include <string>
#include <iostream>
#include <typeinfo>

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
			StringBasedToken(const std::string &aStringValue) : stringValue("") {  stringValue=aStringValue;}; // constructor
			const std::string& getStringValue( ) const { return stringValue;} // return the stringValue //getter function
			void print(std::ostream& str) const { Token::print(str); str << stringValue; }
        };

        class punctuator:public StringBasedToken {
        	// ';', ':', '*', '(', ')'
        private:
		std::string punctuator_variable;

        public:
        	/*Fill in the implementation for constructor */
		punctuator();

        punctuator(std :: string value1): StringBasedToken(value1), punctuator_variable("")
		{
			punctuator_variable=value1;
		};


        };

        class id:public StringBasedToken
        {
			// identifiers -- example:  sum
        public:
        	/*Fill in the implementation for constructor */
        };

        class type_spec:public StringBasedToken
		{
			// 'char' | 'int' | 'float'
        public:
        	/*Fill in the implementation for constructor  */
		};

        class assignment_operator:public StringBasedToken
		{
			// '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|='
        public:
        	/*Fill in the implementation for constructor  */
		};

        class conditional_operator:public StringBasedToken
		{
			// '?'
        public:
        	/*Fill in the implementation for constructor  */
		};

        class shift_operator:public StringBasedToken
		{
			// '<<' | '>>'
        public:
        	/*Fill in the implementation for constructor  */
		};

        class additive_operator:public StringBasedToken
		{
			// '+' | '-'
        public:
        	/*Fill in the implementation for constructor  */
		};

        class div_operator:public StringBasedToken
		{
			// '/' | '%'
        public:
        	/*Fill in the implementation for constructor  */
		};

        class unary_operator:public StringBasedToken
		{
			// '&' | '~'
        public:
        	/*Fill in the implementation for constructor  */
		};

        class postfix_operator:public StringBasedToken
		{
			// '++' | '--'
        public:
        	/*Fill in the implementation for constructor  */
		};

        class string:public StringBasedToken
        {
        	// e.g., "sample string"
        public:
        	/*Fill in the implementation for constructor  */
        };

        class incorrect:public StringBasedToken
		{
			// e.g., "sample string     --> This is incorrect ...
        	//		(quotation mark " is missing at the end)
		public:
			/* Fill in the implementation for constructor. Store a warning message */
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

        	const T& getValue() const { /*Fill in the implementation */ }
        	void print(std::ostream& str) const {Token::print(str); str << ": " << value; }
		};



} // namespace ensc251

#endif /* PARSERCLASSES_HPP_ */
