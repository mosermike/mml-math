/**
 * @brief Source File of the Shunting-Yard-Algorithm
*/

#include <iostream>
#include <vector>
#include <string>
#include <cctype> // std::isdigit
#include <stack>
#include <math.h>
#include <map>
#include <mml/standards.hpp>

#include "mml-math/shunting_yard_algorithm.hpp"

/**
 * @brief Checks if there is an invalid operator pair
 * 
 * If there are two operators after each other, except for '-' in the second position,
 * the code will print a segmentation error
 * 
 * @param equation Equation to be checked
 * @return true 
 * @return false 
 */
bool invalidOperatorPair(const mml::string& equation) {
	if(equation.exist("++","+*","+/","+^","**","*+","*/","*^","/+","/*","/^"))
		return true;
	return false;
}

std::vector<mml::string> mml::math::shunting_yard_algorithm::equation_to_infix(bool verbose) {
    mml::string number = "";

    if(equation.empty())
        throw std::runtime_error("[equation_to_infix] Equation is empty.");

    if(verbose)
        std::cout << "[equation_to_infix] Process equation " << equation << std::endl;

	// Check if an operator appears directly after another
	if(invalidOperatorPair(equation))
		throw std::invalid_argument("[equation_to_infix] Operator directly after another operator detected.");

    // Clear the infix vector
    infix.clear();
    
    for(size_t i = 0; i < equation.size(); i++) {
        char c = equation[i];
		
		// Character is a number, a decimal point or starts with a minus
        if(mml::isnum(c) || c == '.' || (c == '-' && i == 0) || (c == '-' && number.empty() && infix[infix.size()-1] != ")")) {
            number += c;
		}
		// Check if e is used as 10^
		else if (i < equation.size()-1 && c == 'e' && (equation[i+1] == '-' || equation[i+1] == '+' || mml::isnum(equation[i+1])) ) {
            number += c;
			// Also add the next character
			number += equation[i+1];
			i++;
		}

        else {
            if (!number.empty()) {
                infix.push_back(number);
                number.clear();
            }
            if(std::isalpha(c)) {
                mml::string temp(c);
                i++;
                while(std::isalnum(equation[i]))
                    temp += equation[i++];
                --i; // minus 1 because it is a non-alphanumeric char

                if(verbose)
                    std::cout << "[equation_to_infix] Detected alphabetic number " << c << " with the function " << temp << std::endl;

                if (this->functions.count(temp.str()))
                    infix.push_back(temp);
                else
                    throw std::invalid_argument("Unrecognized function or variable: " + temp.str());
            }
            else if (c != ' ') {
                if(verbose)
                    std::cout << "[equation_to_infix] Detected operator " << c << std::endl;
                infix.push_back(mml::string(1, c));
          }
        }
    }

    if (!number.empty()) {
        infix.push_back(number);
    }
    
    return infix;


}

/**
 * Checks whether a string is a number or not
*/
bool isNumber(const std::string& str) {
    if (str.empty()) return false;

    bool hasDecimal = false; // has a decimal point
    bool hasDigit = false; // has a digit

    // Check the first character for '+' or '-'
    size_t i = 0;
    if (str[i] == '+' || str[i] == '-') {
        ++i; // Skip the sign character
    }

    // Iterate through the rest of the characters
    for (; i < str.length(); ++i) {
        // Treat number
        if (std::isdigit(str[i])) {
            hasDigit = true;
        }
        // treat decimal points
        else if (str[i] == '.') {
            if (hasDecimal) return false; // More than one decimal point
            hasDecimal = true;
        }

		// Treat e with 10^
		else if ((str[i] == '-' || str[i] == '+') && i > 0 && str[i-1] == 'e') {
            continue;
        }
        // Treat other character
        else if (str[i] == 'e')
			continue;
        else
			return false; // Invalid character
        
    }

    // At least one digit must be present
    return hasDigit;
}

std::vector<mml::string> mml::math::shunting_yard_algorithm::infix_to_postfix(bool verbose) {

    std::stack<mml::string> operators;

    if(infix.empty())
        throw std::runtime_error("[infix_to_postfix] Infix is empty.");

    if(verbose) {
        std::cout << "[infix_to_postfix] Infix: ";
        for(mml::string& token : infix)
            std::cout << token << " ";
        std::cout << std::endl;
    }
    // Clear the postfix
    postfix.clear();

    for(mml::string& token : infix) {
        if (isNumber(token.str())) {
            postfix.push_back(token);
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
        else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop();
    }

    if(verbose) {
        std::cout << "[infix_to_postfix] Postfix: ";
        for(mml::string& token : postfix)
            std::cout << token << " ";
        std::cout << std::endl;
    }

    return postfix;

}

int mml::math::shunting_yard_algorithm::precedence(mml::string op) noexcept {
    if (op == "+" || op == "-") {
        return 1;
    }
    
	if (op == "*" || op == "/") {
        return 2;
    }
    
	if (op == "^") {
        return 3;
    }

	if (this->functions.count(op.str()))
		return 4;
    return 0;
}




double mml::math::shunting_yard_algorithm::evaluate_postfix(bool verbose) {
    std::stack<double> values;

    if(postfix.empty())
        throw std::runtime_error("[evaluate_postfix] Postfix is empty.");

    if(verbose) {
        std::cout << "[evaluate_postfix] Postfix: ";
        for(mml::string& token : postfix)
            std::cout << token << " ";
        std::cout << std::endl;
    }

    for (mml::string& token : this->postfix) {
        // if token is a number => push to the stack
        if (isNumber(token.str())) {
            values.push(token.atof());
        }
        // Perform an operation
        else {
            // function applies to a value to the right in infix notation
            if (this->functions.find(token.str()) != functions.end()) {
                if(values.empty())
                    throw std::runtime_error("[evaluate_postfix] Invalid syntax for " + token.str());
                double arg = values.top(); values.pop();
                
                if(arg < functions[token.str()].min || arg > functions[token.str()].max)
                    throw std::out_of_range("[" + token.str()+  "] " + std::to_string(arg) + " out of range!");

                if(verbose)
                    std::cout << "[" << token << "] Compute " << token << "(" << arg << ") = " << functions[token.str()].func(arg) << std::endl;
                values.push(functions[token.str()].func(arg));
            }
            else {
                // Get values from the left and the right in infix notation
                double right = values.top(); values.pop();
                double left = values.top(); values.pop();

                // Perform remaining operators
                if (token == "+") {
                    if(verbose)
                        std::cout << "[+] Compute " << left << " + " << right << " = " << left+right << std::endl;
                    values.push(left + right);
                }
                else if (token == "-"){
                    if(verbose)
                        std::cout << "[-] Compute " << left << " - " << right << " = " << left-right << std::endl;
                    values.push(left - right);
                }
                else if (token == "*"){
                    if(verbose)
                        std::cout << "[*] Compute " << left << " * " << right << " = " << left*right << std::endl;
                    values.push(left * right);
                }
                else if (token == "/"){
                    if(verbose)
                        std::cout << "[/] Compute " << left << " / " << right << " = " << left/right << std::endl;
                    values.push(left / right);
                }
                else if (token == "^"){
                    if(verbose)
                        std::cout << "[^] Compute " << left << "^" << right << " = " << std::pow(left, right) << std::endl;
                    values.push(std::pow(left, right));
                }
            }
        }
    }
    if(verbose) {
        std::cout << "[evaluate_postfix] Result is " << values.top() << std::endl;
    }

    this->result = values.top();
    return result;
}

double mml::math::shunting_yard_algorithm::evaluate(bool verbose) {
    // Transform string to infix
    equation_to_infix();

    // Transform infix to postfix
	infix_to_postfix();

    // Evaluate postfix
	double result = evaluate_postfix();

    return result;

}