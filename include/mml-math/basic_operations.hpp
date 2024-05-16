/**
 * @author Mike
 * 
 * @file basic_operations.hpp
 * 
 * @description Enthält verschiedene Basic Rechenoperationen
 * 
*/

#ifndef __math_basic_operations_hpp__
#define __math_basic_operations_hpp__

#include <mml.hpp>

namespace mml {
	namespace rechner {
		
		extern void save_result(shell::arg args, mml::string equation, double result);

		/**
		 * @note Addition von Werten mit Enter als Eingabe
		 * 
		 * @return double
		 * @author mike
		 */
		mml::vector<double> add(mml::shell::arg args);
		/**
		* @note Gleichung mit mehreren Operationen
		* @param args ARguments from shell
		* @param string Equation to be computed
		* @param bool Execute function "replace" to replace operations
		* @return double
		* @author Mike
		*/
		double calculate(mml::shell::arg args, mml::string equation, bool replace = true);
		
		/**
		* @note Mehrere Berechnungen ausführen
		* 
		* @return double
		* @author Mike
		*/
		double calculations(mml::shell::arg args);
		/**
		 * @note Berechnungen ausführen für andere Programme (keine Ausgaben)
		 * 
		 * @return double
		 * @author Mike
		 */
		double calculate_intern(string equation, bool verbose = false, bool replace = true);
		
		/**
		 * @note Werte multiplizieren
		 * 
		 * @return double
		 * @author Mike
		 */
		double multiply(mml::shell::arg args, mml::string, bool replace = true);


		/**
		* @note Werte addieren
		* 
		* @return double
		* @author Mike
		*/
		double summation(mml::shell::arg args, mml::string equation, bool replace = true);

	}
}
#endif
