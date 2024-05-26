/**
 * Performing test for the calculations
*/
#include <mml.hpp>
#include <mml-math.hpp>
#include <iostream>

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
	std::cout << test << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	return 0;
}
