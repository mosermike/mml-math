/**
 * Performing test for the calculations
*/
#include <mml.hpp>
#include <mml-math.hpp>
#include <iostream>

int main() {
	std::cout << "╭──────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for calculations │" << std::endl;
	std::cout << "╰──────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	mml::string test;
	test = "If you can see this without any numbers, then you succesfully installed any dependencies132!";
	test.del_number(true);
	std::cout << test << std::endl;
	std::cout << "Testing of math library starts by calculating 1+1 ..." << std::endl;
	double result = mml::rechner::calculate({"-c"},"1+1");
    std::cout << "The result is " << result << ". Is it 2? ";
	if(result == 2.0)
	 	std::cout << "Yes!"<< std::endl;
	else
	 	std::cout << "No, there is something not working!"<< std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	std::cout << "Testing of math library starts by calculating (2^(3)+2)*3 ..." << std::endl;
	result = mml::rechner::calculate({"-c"},"(2^(3)+2)*3");
	std::cout << "The result is " << result << ". Is it 30? ";
	if(result == 30.0)
	 	std::cout << "Yes!"<< std::endl;
	else
	 	std::cout << "No, there is something not working!"<< std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	return 0;
}
