#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <mml.hpp>

#include "../include/mml-math/functions.hpp"
#include "../include/mml-math/constants.hpp"


mml::string mml::math::replace(mml::string equation) {
	
	// Replace , with .
	equation = equation.replace(",",".");
		
	// ******************************
	// * Replace physical constants *
	// ******************************
	equation = equation.replace("P_a0", std::to_string(P_a0).c_str());
	equation = equation.replace("P_c", std::to_string(P_c).c_str());
	equation = equation.replace("P_mu", std::to_string(P_mu).c_str());
	equation = equation.replace("P_eps", std::to_string(P_eps).c_str());
	equation = equation.replace("P_e", std::to_string(P_e).c_str());
	equation = equation.replace("P_k", std::to_string(P_k).c_str());
	equation = equation.replace("P_h", std::to_string(P_h).c_str());
	equation = equation.replace("P_m", std::to_string(P_m).c_str());
	equation = equation.replace("P_G", std::to_string(P_G).c_str());
	equation = equation.replace("P_u", std::to_string(P_u).c_str());
	equation = equation.replace("P_NA", std::to_string(P_NA).c_str());
	
	// **********************************
	// * Replace mathematical constants *
	// **********************************
	equation = equation.replace("M_Pi",std::to_string(M_PI).c_str());
	equation = equation.replace("pi",std::to_string(M_PI).c_str());

	// Replace e if there is an operator before and after the symbol
	for(uint32_t i = equation.find('e'); i < equation.size(); i++){
		if(equation[i] == 'e') {
			// e at the beginning
			if(i == 0)
				equation = mml::to_string(M_E) + equation.substr(1);
			// e at the end
			else if(!mml::is_num(equation[i-1]) && i == equation.size()-1) {
				equation = equation.sub(0,i-1) + mml::to_string(M_E);
				continue;
			}
			// e somewhere else
			else if(!mml::is_num(equation[i-1]) && (!std::isalnum(equation[i+1])))
				equation = equation.sub(0,i-1) + mml::to_string(M_E) + equation.substr(i+1);
			
		}
		// Look for next e in the equation
		i = equation.find('e',i+1) -1;
		
	}

	return equation;
}


