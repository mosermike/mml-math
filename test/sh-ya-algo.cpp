/**
 * Performing test for the calculations
*/
#include <mml.hpp>
#include "mml-math/shunting_yard_algorithm.hpp"
#include <iostream>

int main(int argc, char **argv) {
	std::cout << "╭─────────────────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for Shunting Yard Algorithm │" << std::endl;
	std::cout << "╰─────────────────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	try {
		mml::shell::arg args(argv,argc);
		mml::string test;
		std::cout << "Testing of math library starts by calculating (1+1)*2²-log10(50+50)*2 ..." << std::endl;
		mml::math::shunting_yard_algorithm sy_algm("(1+1)*2^2+log10(50+50)*2");
		sy_algm.equation_to_infix(args.exist("-v","--verbose"));
		sy_algm.infix_to_postfix(args.exist("-v","--verbose"));
		double result = sy_algm.evaluate_postfix(args.exist("-v","--verbose"));
		std::cout << "The result is " << result << ". Is it 12.0? ";
		if(result == 12.0)
			std::cout << "Yes!"<< std::endl;
		else
			std::cout << "No, there is something not working!"<< std::endl;

		std::cout << std::endl;
		std::cout << "─────────────────────────────────────────────────────" << std::endl;
		std::cout << std::endl;
		
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}
	catch (const std::invalid_argument& e) {
        std::cerr << "Detected Error: " << e.what() << std::endl;
	}
	
	return 0;
}
