/**
 * Performing test for polynomial fits
*/

#include <iostream>
#include <mml.hpp>
#include <cassert>

#include "mml-math/matrix.hpp"
#include "mml-math/polyfit.hpp"


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

	
	std::cout << "╭───────────────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for polynomial regression │" << std::endl;
	std::cout << "╰───────────────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	std::cout << "Compute the polynomial fit for data x = {1,2,3,4}, y = {1,2,4,5} for a second degree polynomial!" << std::endl;
 	mml::math::polyfit pol({1,2,3,4},{1,2,4,5},2);
	mml::math::matrix coeff = pol.fit(true);

	coeff.print();

	assert_msg((std::round(coeff(0,0) * 10.0) / 10.0 == -0.5), "Polynomfit for second degree failed. The first coefficient should be -0.5");
	assert_msg((std::round(coeff(1,0) * 10.0) / 10.0 == 1.4) , "Polynomfit for second degree failed. The second coefficient should be 1.4");
	assert_msg((std::round(coeff(2,0) * 10.0) / 10.0 == 0.0) , "Polynomfit for second degree failed. The third coefficient should be 0.0");

	pol.covar.print();

	assert_msg((std::round(pol.covar.sum()*100.0)/100.0 == 0.19) , "Sum of covariance matrix is not 0.19 as expected. The result is " + std::to_string(pol.covar.sum()) + "");
	
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return 0;



}

