/**
 * @author Mike
 * 
 * @file logging.hpp
 * 
 * @description Enthält Funktionen zum Loggen
 * 
*/

#ifndef __math_logging_hpp__
#define __math_logging_hpp__

#include <mml.hpp>

	namespace mml{
		namespace rechner {
			
			/**
			* @note Logfile backup
			* 
			* @author Mike
			*/
			void backup_logfile(shell::arg args);
			
			/**
			* @note Nullen am Ende löschen
			* 
			* @author Mike
			*/
			mml::string delete_zeros(double equation);
		
			/**
			* @note Altes Ergebnis speichern
			* 
			* @author Mike
			*/
			void save_matrix(mml::shell::arg args, mml::string matrix_equation, mml::string matrix_result);
			void save_result(shell::arg args, mml::string equation, double result);
			
			
			/**
			* @note Logfile zurücksetzen
			* 
			* @author Mike
			*/
			void reset_logfile(shell::arg args);
		}
	}
#endif
