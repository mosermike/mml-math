/**
 * Performing test for the calculations
*/
#include <mml.hpp>
#include "mml-math/shunting_yard_algorithm.hpp"
#include <iostream>

// Custom assert macro
#define assert_msg(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed: (" #cond "), function " << __func__ \
                      << ", file " << __FILE__ << ", line " << __LINE__ << "." << std::endl \
                      << "Message: " << msg << std::endl; \
            std::abort(); \
        } \
    } while (false)
	
int main(int argc, char **argv) {
	std::cout << "╭─────────────────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for Shunting Yard Algorithm │" << std::endl;
	std::cout << "╰─────────────────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	mml::shell::arg args(argv,argc);
	mml::string test;
	std::cout << "Testing of math library starts by calculating (1+1)*2²-log10(50+50)*2 ..." << std::endl;
	mml::math::shunting_yard_algorithm sy_algm("(1+1)*2^2+log10(50+50)*2");
	sy_algm.equation_to_infix(args.exist("-v","--verbose"));
	sy_algm.infix_to_postfix(args.exist("-v","--verbose"));
	double result = sy_algm.evaluate_postfix(args.exist("-v","--verbose"));
	std::cout << "The result is " << result << ". Is it 12.0? ";
	assert_msg((result == 12.0), "No, there is something not working!");
	std::cout << "Yes!"<< std::endl;
	
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
		
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	
	return 0;
}
