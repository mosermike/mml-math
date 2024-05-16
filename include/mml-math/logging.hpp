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
			* @param args Arguments from the shell
			* @param string Logfile
			* @author Mike
			*/
			void backup_logfile(shell::arg args, std::string logfile);
			
			/**
			* @note Nullen am Ende löschen
			* @param double number
			* @return string
			* @author Mike
			*/
			mml::string delete_zeros(double equation);
		
			/**
			* @note Altes Ergebnis speichern
			* @param args Arguments from the shell
			* @param string equation
			* @param string result
			* @param string Logfile
			* @author Mike
			*/
			void save_matrix(mml::shell::arg args, mml::string matrix_equation, mml::string matrix_result, std::string logfile);
			void save_result(shell::arg args, mml::string equation, double result, std::string logfile);
			
			
			/**
			* @note Logfile zurücksetzen
			* @param args Arguments from the shell
			* @param string Logfile
			* @author Mike
			*/
			void reset_logfile(shell::arg args, std::string logfile);
		}
	}
#endif
