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

void mml::rechner::backup_logfile(shell::arg args, std::string logfile) {
	
	mml::log log(logfile);
	log.backup(args.exist("-v","--verbose"));
}

mml::string mml::rechner::delete_zeros(double result) {
	
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

void mml::rechner::reset_logfile(shell::arg args, std::string logfile) {
	
	mml::log log(logfile);
	
	log.reset(args.exist("-v","--verbose"));
}


void mml::rechner::save_result(mml::shell::arg args, mml::string equation, double result, std::string logfile) {
	
	mml::log log(logfile);
	
	equation = equation + " = " + delete_zeros(result).str();
	if(args.exist("-k","--comment"))
		equation = equation + "  \\\\ " + args[args.positionArg("-k","--comment") + 1].str();
	
	log << equation;
}

void mml::rechner::save_matrix(mml::shell::arg args, mml::string matrix_equation, mml::string matrix_result, std::string logfile) {
	
	mml::log log(logfile);
	
	if(args.exist("-k","--comment"))
		matrix_result = matrix_result + "  \\\\ " + args[args.positionArg("-k","--comment") + 1].str();
	
	log << matrix_equation + " = " + matrix_result.str();
}
