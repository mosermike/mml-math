/**
 * @author Mike
 * 
 * @file functions.hpp
 * 
 * @description Enthält verschiedene Funktionen
 * 
*/

#ifndef __math_functions_hpp__
#define __math_functions_hpp__

#include <iostream>
#include <mml.hpp>
// #include "basic_operations.hpp"
namespace mml {
	namespace rechner {
		
		/**
		 * Grad zu Radiant
		 * 
		 * @return Wert in Radiant
		 * @author Mike
		 */
// 		double grad_to_rad(double grad);
		
		/**
		 * Zu einem Operator berechnungen durchführen
		 * 
		 * 
		 * @author Mike
		 */
		mml::string operations(mml::shell::arg args, mml::string equation, mml::string command, uint16_t tabs);
			
		/**
		 * @note Position der richtigen Klammer zu berechnen
		 * 
		 * @return neue Position
		 * @author Mike
		 */
		std::size_t pos_bracket(mml::string equation, std::size_t temp, std::size_t temp_end);
		
		/**
		 * Radiant oder Grad wenn in args --grad
		 * 
		 * @return Wert in Grad oder Radiant
		 * @author Mike
		 */
		double rad_or_grad(mml::shell::arg args, double grad);
		double grad_or_rad(mml::shell::arg args, double grad); // nach Befehl wieder in richtigem Format
		/**
		 * Radiant zu Grad
		 * 
		 * @return Wert in Grad
		 * @author Mike
		 */
// 		double rad_to_grad(double rad);
		
		/**
		 * @note Verschiedene Operatoren durchführen
		 * 
		 * @author Mike
		 */
		mml::string rechnung(mml::shell::arg args, mml::string equation, uint16_t tabs = 0);
		/**
		* @note Sachen ersetzen und auch bestimmte Funktionen(sqrt,^) berechnen
		* 
		* @param args Arguments from the shell.
		* @param equation Equation to calculate and replace.
		* @param tabs For verbose, how many tabs are printed to show hierarchy of calculation.
		* 
		* @return Replaced string with the result
		*
		* @author Mike
		*/
		mml::string replace(mml::shell::arg args, mml::string equation);
		
	}
}


#endif
