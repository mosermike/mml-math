/**
 * @author Mike
 * 
 * @file matrix.hpp
 * 
 * @note 
 * 
*/

#ifndef __math_matrix_hpp__
#define __math_matrix_hpp__

#include <mml.hpp>

namespace mml {
	namespace rechner {
		
		mml::string matrix_calculation(mml::shell::arg args, mml::string matrix);
		
		/**
		 * @note Matrix addieren oder subtrahieren
		 * 
		 * @return Erebnis als String
		 * @author Mike
		 */
		mml::string matrix_addition(mml::string matrix1, mml::string matrix2, char op = '+', bool ausgabe = false);
		/**
		 * @note Adjunkte einer Matrix bestimmen (wird für Inverses benötigt)
		 * 
		 * @return Erebnis als String
		 * @author Mike
		 */
		mml::string matrix_adjunct(mml::string matrix, bool ausgabe = false);
		/**
		 * @note Determinante einer Matrix bestimmen
		 * 
		 * @return Erebnis als double
		 * @author Mike
		 */
		double matrix_determinante(string matrix, const bool ausgabe);
		/**
		 * @note Inverse einer Matrix bestimmen
		 * 
		 * @return Erebnis als String
		 * @author Mike
		 */
		mml::string matrix_inverse(mml::string matrix, bool ausgabe = false);
		/**
		 * @note Matrizen multiplizieren
		 * 
		 * @return Erebnis als String
		 * @author Mike
		 */
		mml::string matrix_multiply(mml::string matrix1, mml::string matrix2, bool ausgabe = false);
		/**
		 * @note Matrix ohne bestimmte Zeile und Linie
		 * 
		 * @return Erebnis als String
		 * @author Mike
		 */
		mml::string matrix_smaller(mml::string matrix, uint32_t row, uint32_t column, bool ausgabe = false);
		/**
		 * @note Matrix ausgeben
		 * 
		 * @return Erebnis als String
		 * @author Mike
		 */
		void matrix_print(mml::string matrix);
		/**
		 * @note Matrix transponieren
		 * 
		 * @return Erebnis als String
		 * @author Mike
		 */
		mml::string matrix_transposed(mml::string matrix, bool ausgabe = false);
	}
}


#endif // __matrix_hpp__
