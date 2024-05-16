#include <mml.hpp>
#include <mml-math.hpp>
#include <iostream>

int main() {
	mml::string test;
	test = "If you can see this without any numbers, then you succesfully installed any dependencies132!";
	test.del_number(true);
	std::cout << test << std::endl;

	std::cout << "Testing of math library starts by calculating 1+1 ..." << std::endl;
	double result = mml::rechner::calculate({"-c"},"1+1");
        std::cout << "The result is " << result << ". Is it 2? If yes, then congrats, everything works." << std::endl;

	return 0;
}
