/**
 * @author Mike
 * 
 * @file logging.hpp
 * 
 * @brief Functions for logging calculations
 * 
*/

#ifndef mml_math__include__mml_math__logging_hpp
#define math_logging_hpp__

#include <mml.hpp>

	namespace mml{
		namespace rechner {
			
			/**
			* @brief Logfile backup
			* @param args Arguments from the shell
			* @param logfile Logfile
			*/
			void backup_logfile(shell::arg args, std::string logfile);
			
			/**
			* @brief Delete zeros at the end
			* @param equation number
			* @return string
			*/
			mml::string delete_zeros(double equation);
		
			// TODO save matrix
			/**
			* @brief Save old result
			* @param args Arguments from the shell
			* @param matrix_equation equation
			* @param matrix_result result
			* @param logfile Logfile
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
