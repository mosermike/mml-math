/**
 * Performing test for the calculations
*/
#include <mml.hpp>
#include <iostream>
#include <cassert>
#include <cctype>

#include "mml-math.hpp"

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

int main() {
	std::cout << "╭──────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for dependencies │" << std::endl;
	std::cout << "╰──────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	mml::string test;
	test = "If you can see this without any numbers, then you succesfully installed any dependencies132!";
	test.del_number(true);
	for(char i : test) {
		assert_msg(!mml::isnum(i), ("Character " + std::to_string(i) + ", which is a number!"));
	}
	std::cout << test << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	return 0;
}
