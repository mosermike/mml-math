/**
 * @author Mike Moser
 * @file functions.hpp
 * @brief Misc. functions
*/

#ifndef mml_math_include_mml_math_functions_hpp
#define mml_math_include_mml_math_functions_hpp

#include <iostream>
#include <mml.hpp>

namespace mml {
	namespace math {
		/**
		* @brief Replace constants with their values
		* 
		* @param equation Equation where constants are replaced
		* 
		* @return Replaced string with the result
		*/
		mml::string replace(mml::string equation);
		
	}
}


#endif
