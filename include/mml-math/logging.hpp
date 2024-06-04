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
		namespace math {
			
			/**
			* @brief Logfile backup
			* @param args Arguments from the shell
			* @param logfile Logfile
			*/
			void backup_logfile(std::string logfile, bool verbose);
			
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
			void save_matrix(mml::string matrix_equation, mml::string matrix_result, std::string logfile, mml::string comment = "");
			void save_result(mml::string equation, double result, std::string logfile, mml::string comment = "");
			
			
			/**
			* @note Logfile zurücksetzen
			* @param args Arguments from the shell
			* @param string Logfile
			* @author Mike
			*/
			void reset_logfile(std::string logfile, bool verbose);
		}
	}
#endif
