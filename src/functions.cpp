#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <mml.hpp>

#include "../include/mml-math/functions.hpp"
#include "../include/mml-math/constants.hpp"


mml::string mml::math::replace(mml::string equation, bool verbose) {
	
	if(verbose)
        std::cout << "[replace] Process equation " << equation << std::endl;
	// Replace , with .
	equation = equation.replace(",",".");
		
	// ******************************
	// * Replace physical constants *
	// ******************************
	equation = equation.replace("P_a0", P_a0);
	equation = equation.replace("P_c", P_c);
	equation = equation.replace("P_mu", P_mu);
	equation = equation.replace("P_eps", P_eps);
	equation = equation.replace("P_e", P_e);
	equation = equation.replace("P_k", P_k);
	equation = equation.replace("P_h", P_h);
	equation = equation.replace("P_m", P_m);
	equation = equation.replace("P_G", P_G);
	equation = equation.replace("P_u", P_u);
	equation = equation.replace("P_NA", P_NA);
	
	

	// **********************************
	// * Replace mathematical constants *
	// **********************************
	equation = equation.replace("M_Pi",std::to_string(M_PI).c_str());
	equation = equation.replace("pi",std::to_string(M_PI).c_str());

	// Replace e if there is an operator before and after the symbol
	for(uint32_t i = equation.find('e'); i < equation.size(); i++){
		if(equation[i] == 'e') {
			if(verbose)
        		std::cout << "[replace] Detected 'e' at position " << i << std::endl;
			// e at the beginning but not part of exp
			if(i == 0 && equation[i+1] != 'x')
				equation = mml::to_string(M_E) + equation.substr(1);
			// e at the end
			else if(!mml::isnum(equation[i-1]) && i == equation.size()-1) {
				equation = equation.sub(0,i-1) + mml::to_string(M_E);
				continue;
			}
			// e somewhere else
			else if(!mml::isnum(equation[i-1]) && (!std::isalnum(equation[i+1])))
				equation = equation.sub(0,i-1) + mml::to_string(M_E) + equation.substr(i+1);
			
		}
		// Look for next e in the equation
		i = equation.find('e',i+1) -1;
		
	}

	if(verbose)
        std::cout << "[replace] Replaced all constants: " << equation << std::endl;

	return equation;
}


