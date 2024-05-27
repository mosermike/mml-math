/**
 * @author Mike Moser
 * @date 26.05.2024
 * @name calculator
 * @file main.cpp
 * @version 1
 * @details Computations of different things with the console
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>	// setprecision
#include <signal.h>
#include <mml.hpp>
#include "mml-math.hpp"

#ifndef calc_log
#define calc_log 		"./calc.log"
#endif

/**
* @note Help Page
* @return None
*/
void help() {

	mml::help::header("Computes different things by using the shell.");
	
	std::cout << "\tThis program executes calculations depending on arguments." << std::endl;
	std::cout << "\tBy the use of brackets, quotation marks are necessary."	<< std::endl << std::endl;
	std::cout << "\tNecessary arguments for long options are also necessary for short ones." << std::endl;
	mml::shell::option("-a, --adjugate" , "Computes adjugate of a matrix given as -m [...].");
	mml::shell::option("-c, --calculate" , "Solves an equation.");
	mml::shell::option("-cs, --calculations" , "Solves many equations.");
	mml::shell::option("-d, --det" , "Computes the determinant of a matrix given as -m [...].");
	mml::shell::option("-h, --help" , "Prints this help.");
	mml::shell::option("-i, --inverse" , "Computes the inverse of a matrix given as -m [...].");
	mml::shell::option("-k, --comment"  , "Additional comment to be written into the log file after the equation.");
	mml::shell::option("-l, --log"  , "Print the log file.");
	mml::shell::option("-lr, --log_reset", "Resets the logfile.");
	mml::shell::option("-lb, --log_backup", "Backup of the log file.");
	mml::shell::option("-m, --matrix" , "Calculation of a matrix equation or the matrix used for other matrix operators. Matrix form [[1.,row],[2.,row]]");
	mml::shell::option("-ml, --matrix-latex" , "Format in Latex. (beta)");
	mml::shell::option("-t, --timer", "Prints the duration of the calculation.");
	mml::shell::option("-tr, --transpose" , "Computes the transpose of a matrix given as -m [...].");
	//mml::shell::option("-u" , "Wertzuweisung einer oder mehreren unbekannten Variable(n) mit Trennzeichen ':' in der Gleichung. z.B. -u x=2");
	mml::shell::chapter("Existing operators:", true);
	mml::shell::option("+" , "Addition.");
	mml::shell::option("-" , "Subtraction.");
	mml::shell::option("*", "Multiplication.");
	mml::shell::option("/" , "Division.");
	//mml::shell::option("d" , "Ableiten einer Funktion. Direkt als Parameter übergeben(alt).");
	mml::shell::option("^" , "Power calculation.");
	mml::shell::option("exp(x)" , "Computes the exponential funciton of x.");
	mml::shell::option("sin(x)" , "sin calculations of x (given in rad).");
	mml::shell::option("cos(x)" , "cos calculations of x (given in rad).");
	mml::shell::option("tan(x)" , "tan calculations of x (given in rad).");
	mml::shell::option("asin(x)" , "arcsin calculations of x.");
	mml::shell::option("acos(x)" , "arccos calculations of x.");
	mml::shell::option("atan(x)" , "arctan calculations of x.");
	mml::shell::option("ln(x)" , "logarithm naturalis of x.");
	mml::shell::option("log(x)" , "10th Logarithm of x.");
	mml::shell::option("sqrt(x)" , "Square root of x.");
	std::cout << std::endl;
	mml::shell::chapter("Options of --calculations:",true);
	mml::shell::option("rx", "use of another result, rx will be replaced in the new equation.");
	std::cout << std::endl;
	mml::shell::chapter("Others:", true);
	std::cout << "\tExisting constants: pi, exp, E, P_c, P_k, P_m, P_e, P_eps, P_G, P_h, P_mu, P_NA, P_u" << std::endl;

	mml::help::foot("1", "May", 2024);
}

/**
 * @brief Adds values which are written interactively
 * @return vector with all the values written
*/
mml::vector<double> add() {
	mml::string				temp_s		= "";
	mml::vector<double>		values;

	std::cout << "[Addition] Write the values (Finish with 'a', go back with 'z'): " << std::endl;
		
	double temp_d = 0.0;
	for(uint32_t i = 0;; i++) {
		std::cin >> temp_s;
		
		if(temp_s.exist("a")){
			break;
		}
		if(temp_s.exist("z") && values.size() > 0){
			values.pop_back();
			continue;
		}
		temp_s = temp_s.replace(",",".");
		temp_s = mml::math::replace(mml::to_string(temp_s));
		mml::math::shunting_yard_algorithm sh_ya_al(temp_s);
		temp_d = sh_ya_al.evaluate();
		values.push_back(temp_d);
	}

	return values;
}

double calculate(mml::string equation, bool verbose = false){

	// Write the equation to the algorithm class
	mml::math::shunting_yard_algorithm sy_algm(equation);
	
	// Convert the equation to infix
	sy_algm.equation_to_infix(verbose);
	
	// Convert infix to postfix
	sy_algm.infix_to_postfix(verbose);
	
	// Evaluate postfix
	double result = sy_algm.evaluate_postfix(verbose);
	
	return result;
}
	
/**
 * @brief Calculates mutliple equations interactively
 * @param verbose Verbose output
 * @param equations Reference of a vector where all the equations are put
 * @return All the results as a vector
 * @throw invalid_argument : if x in rx is not a number, for using a previous result
*/
std::vector<double> calculations(bool verbose, std::vector<mml::string> &equations) {
	
	double					result			= 0;
	mml::string				equation		= "";
    mml::string				equation_save	= "";
	std::vector<double>		results;
	
		
		while(1) {
			std::cout << "Input of the equation " + std::to_string(results.size() + 1) << ": ";
			

			std::cin >> equation;
			if(equation == "q")
				return results;
			equation_save = equation;
			
			// Pressed Ctrl+D
			if(equation == "") {
				std::cout << std::endl;
				kill(getpid(),SIGTERM);
			}

			// Take old result
			if(equation.exist("r")) {
				std::size_t pos = equation.find("r");
				
				do {
					
					// use of sqrt
					if(equation[pos+1] == 't') {
						pos = equation.find("r",pos + 1);
						continue;
					}
					// use of acos
					if(equation[pos+1] == 'c') {
						pos = equation.find("r",pos + 1);
						continue;
					}

					size_t a = pos+1;
					std::string num = "";
					if(std::isalpha(equation[a]))
						throw std::invalid_argument("Error: Wrong format for option rx! x must be a number!");

					// Add until an operator comes
					while(mml::is_num(equation[a])) {
						num += equation[a++];
						// Catch if the replacement is at the end
						if(a >= equation.size())
							break;
					}

					equation = equation = equation.replace("r" + num, std::to_string(results[std::atoi(num.c_str()) - 1]));
					
					pos = equation.find("r");
				} while(mml::range(pos));
			}
			
			equation = mml::math::replace(equation); // Replacing constants
			result = calculate(equation, verbose);
			results.push_back(result);
			equations.push_back(equation_save);
			std::cout << "Result: " << result << std::endl;
			         
			// Catch ctrl-D:
			equation = "";
		}
	
	return results;
}


int main(int argc, char **argv) {
	
	mml::shell::arg		args		(argc,argv);
	mml::Timer			time		;
	double				result		= 0;
	mml::string			matrix		= "";
	
	if(args.notArg("-t","--timer"))
		time.stop();
		
	if(args.size() == 1){
		throw std::logic_error("Missing input of the wished operation. Use '-h' for help.");
	}
	
	else if (args.findArg("--help","-h")) {
		help();
		return 0;
	}
	
	else if ((args.findArg("-c","--calculate") || args.findArg("-m","--matrix")) && args.size() == 2) {
		throw std::logic_error("Missing Equation!");
	}
	
	else if (args.findArg("-c","--calculate")) {
		mml::string equation = mml::math::replace(args[args.positionArg("-c") + 1]);
		result = calculate(equation, args.exist("-v","--verbose"));
        mml::rechner::save_result(args, args[args.positionArg("-c","--calculate") + 1],result,calc_log);
    }
	
	else if (args.findArg("-cs","--calculations")) {
		std::vector<mml::string> equations;
		std::vector<double> results = calculations(args.exist("-v","--verbose"), equations);
		
		// Save the results and equations
		for(uint32_t i = 0; i < equations.size(); i++)
			mml::rechner::save_result(args, equations[i], results[i],calc_log);
	}

	else if(args.findArg("-m","--matrix")) {

		/**
		 * NOTE Transform from latex matric to compatible format
		 * TODO
		 */
		
		if(args.findArg("-ml","--matrix-latex")) {
			mml::string temp = args[args.positionArg("-m","--matrix") + 1]; // Line with the matrix calculations
			mml::string temp_s = ""; // string to build the new calculations line
			bool braket = false;	// to indicate whether the matrix is finished or starts
			// Build string in compatible format:
			for(uint32_t i = 0; i < temp.size();i++) {
				if(temp[i] == '&')
					temp_s += ",";
				else if(temp[i] == '\\')
					temp_s += "],[";
				else if(temp[i] == '|' and braket){
					temp_s += "]]";
					braket = false;
				}
				else if(temp[i] == '|' and not braket) {
					temp_s += "[[";
					braket = true;
				}
				else
					temp_s = temp_s.str() + (char) temp[i];
			}
			args[args.positionArg("-m","--matrix") + 1] = temp_s;
		}

		args[args.positionArg("-m","--matrix") + 1] = args[args.positionArg("-m","--matrix") + 1].replace(" ",""); // Leerzeichen ersetzen, aber Achtung Matrix falsch wenn nicht mit " "
		
		if (args.findArg("-a","--adjugate")) {
			
			mml::matrix::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The adjugate of the matrix" << std::endl;
				mat.print();
				std::cout << "is" << std::endl;
			}
			else
				std::cout << "The adjugate is" << std::endl;
			
			mat = mat.adjugate();
			mat.print();
			return 0;

		}
		else if (args.exist("-d","--det")) {
			mml::matrix::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The determinant of the matrix" << std::endl;
				mat.print();
				std::cout << "is " << mat.det()<< "." << std::endl;
			}
			else
				std::cout << "The determinant is " << mat.det() << "." << std::endl;
			// TODO save matrix
		}
		else if (args.findArg("-i","--inverse")) {
			
			mml::matrix::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The inverse of the matrix" << std::endl;
				mat.print();
				std::cout << "is" << std::endl;
			}
			else
				std::cout << "The inverse matrix is" << std::endl;
			
			mat = mat.inverse();
			mat.print();
			// TODO save matrix

		}
		else if (args.findArg("-tr","--transpose")) {
			
			mml::matrix::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The transpose of the matrix" << std::endl;
				mat.print();
				std::cout << "is" << std::endl;
			}
			else
				std::cout << "The transposed matrix is" << std::endl;
			
			mat = mat.transpose();
			mat.print();
			// TODO save matrix
		}
		else {
			mml::matrix::matrix res = mml::matrix::calc(args[args.positionArg("-m","--matrix") + 1], args.exist("-v","--verbose"));
			std::cout << "The result is" << std::endl;
			res.print();
			//mml::rechner::save_matrix(args, args[args.positionArg("-m","--matrix") + 1], matrix,calc_log);
		}
	}
	else if (args.findArg("-s","--summation")){
		mml::vector<double> values = add();
		result = values.sum();
		values.log(calc_log, false, "[summation] ", " = " + std::to_string(result));
	}
	else if (args.findArg("-l","--log","-lv")) {
		if(mml::Unix::exist(calc_log)) {
			
			mml::log log(calc_log);
			log.print(args.exist("-v","--verbose","-lv"));
		}
		else
			throw std::runtime_error("No existing log file!");
		return 0;
		
	}
	else if(args.findArg("-lr", "log_reset")) {
		mml::rechner::reset_logfile(args,calc_log);
		return 0;
	}
	
	else if(args.findArg("-lb","--log-backup")) {
		mml::rechner::backup_logfile(args, calc_log);
		return 0;
	}
	else {
		mml::string equation = mml::math::replace(args[1]);
		result = calculate(equation, args.exist("-v","--verbose"));
        mml::rechner::save_result(args, args[1],result,calc_log);
    }
	
	if(!args.findArg("-m","--matrix"))
		std::cout << "Result: " << result << std::endl;
		
	if(args.findArg("-t","--timer"))
		std::cout << "Calculation time: " << time.range() << std::endl;

	return 0;
	
}
