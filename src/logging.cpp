/**
 * : @author Mike Moser
 * : @date 07.03.2020
 * : @file logging.cpp
 * : 
 * : 
 * : Beschreibung: 
 * : Logging Informationen
 * :
 * :
 * :
 * :
 */

#include <mml.hpp>
#include <vector>
#include <string>
#include "../include/mml-math/logging.hpp"

void mml::math::backup_logfile(std::string logfile, bool verbose) {
	
	mml::log log(logfile);
	log.backup(verbose);
}

mml::string mml::math::delete_zeros(double result) {
	
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

void mml::math::reset_logfile(std::string logfile, bool verbose) {
	
	mml::log log(logfile);
	
	log.reset(verbose);
}


void mml::math::save_result(mml::string equation, double result, std::string logfile, mml::string comment) {
	
	mml::log log(logfile);
	
	equation = equation + " = " + delete_zeros(result).str();
	if(comment != "")
		equation = equation + "  \\\\ " + comment;
	
	log << equation;
}

void mml::math::save_matrix(mml::string matrix_equation, mml::string matrix_result, std::string logfile, mml::string comment) {
	
	mml::log log(logfile);
	
	if(comment != "")
		matrix_result = matrix_result + "  \\\\ " + comment;
	
	log << matrix_equation + " = " + matrix_result.str();
}
