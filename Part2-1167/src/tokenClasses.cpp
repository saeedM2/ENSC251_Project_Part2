/*
 * tokenClasses.cpp
 *
 *  Created on: Oct 2, 2016
 *      Author: wcs
 */

#include "tokenClasses.hpp"

// I'm not sure if next line works with other than GNU compiler
#include <cxxabi.h>


namespace ensc251 {

char *demangle(const char *typeName) {
	int status;
	// I'm not sure if the below line works with compilers other than GNU
	return abi::__cxa_demangle(typeName, 0, 0, &status);
}

}

