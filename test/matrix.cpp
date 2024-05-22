#include <mml-math/matrix1.hpp>
#include <iostream>
#include <mml.hpp>


int main() {
	std::cout << "Performing test for matrix calculations" << std::endl;
 	mml::math::matrix mat1(3,3);
	mat1(0,0) = 1.0;
	//mat1.print();

	mml::math::matrix mat2("[[1,0,0],[0,1,0],[0,0,1]]");
	mml::math::matrix mat3("[[2,0,0],[0,3,0],[0,0,4]]");
	mat2("[[1,0,0]]");
	mml::math::matrix mat33("[[20,0,0],[100,3,0],[1000,0,4]]");

	mat2.print();
	mat33.print();

	mml::math::matrix mat4 = mat2*mat33;
	std::cout << "TEST" << std::endl;
	mml::math::print_2matrix(mat2," * ",mat33);
	mml::math::print_3matrix(mat2," * ",mat33, " = ", mat4);

	mat4.print();

	mml::math::matrix mat5("[[3,2,0],[1,1,1],[1,2,3]]");
	mat5.print();
	std::cout << mat5.det() << std::endl;
	mml::math::matrix res = mat5.inverse();
	res.print();
	return 0;



}

