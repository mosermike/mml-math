/**
 * Performing test for the matrix calculations
*/
#include <mml-math/matrix1.hpp>
#include <iostream>
#include <mml.hpp>


int main() {
	std::cout << "Performing test for matrix calculations" << std::endl;

	std::cout << "------------------------------------------------------" << std::endl;
 	mml::math::matrix mat1(3,3);
	mat1(0,0) = 1.0;
	std::cout << "The output should be a matrix where only the element (0,0) has the value 1:" << std::endl;
	mat1.print();

	mml::math::matrix mat2("[[1,0,0],[0,1,0],[0,0,1]]");
	mml::math::matrix mat3("[[2,0,0],[0,3,0],[0,0,4]]");
	mat2("[[1,0,0]]");
	mml::math::matrix mat33("[[20,0,0],[100,3,0],[1000,0,4]]");

	std::cout << "------------------------------------------------------" << std::endl;
	mml::math::matrix mat4 = mat2*mat33;
	
	std::cout << "The output should be the multiplication of two matrices:" << std::endl;
	mml::math::print_3matrix(mat2," * ",mat33, " = ", mat4);

	std::cout << "------------------------------------------------------" << std::endl;
	mml::math::matrix mat5("[[3,2,0],[1,1,1],[1,2,3]]");
	mat5.print();
	std::cout << "The output should be the determinant of the matrix printed before (should be -1): " << mat5.det() << std::endl;
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return 0;



}

