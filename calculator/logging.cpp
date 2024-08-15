/**
 * @file logging.cpp
 * @author Mike Moser
 * @brief Implementations of the functions from logging.hpp
 * @version 1.0
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <mml.hpp>
#include <vector>
#include <string>
#include "logging.hpp"

void backup_logfile(std::string logfile, bool verbose) {
	
	mml::log log(logfile);
	log.backup(verbose);
}

mml::string delete_zeros(double result) {
	
	mml::string		result_str	= mml::to_string(result);
	mml::string		temp		= result_str.substr(result_str.find('.')+1);
	mml::string		temp1		= result_str.substr(0,result_str.find('.')+1);
	std::size_t		length		= temp.size();
	bool			comma		= false; // only delete zeros after the comma not before
	
	for(uint32_t i = length - 1; i > 0; i--) {
		if(temp[i] == '.')
			comma = true;
		if(!comma)
			continue;
		if(temp[i] == '0')
			temp = temp.substr(0,temp.size() - 1);
		else
			break;
	}
	
	return temp1 + temp;
}

void reset_logfile(std::string logfile, bool verbose) {
	
	mml::log log(logfile);
	
	log.reset(verbose);
}


void save_result(mml::string equation, double result, std::string logfile, mml::string comment) {
	
	mml::log log(logfile);
	
	equation = equation + " = " + delete_zeros(result).str();
	if(comment != "")
		equation = equation + "  \\\\ " + comment;
	
	log << equation << std::endl;
}

void save_matrix(mml::string matrix_equation, mml::string matrix_result, std::string logfile, mml::string comment) {
	
	mml::log log(logfile);
	
	if(comment != "")
		matrix_result = matrix_result + "  \\\\ " + comment;
	
	log << matrix_equation + " = " + matrix_result.str();
}
