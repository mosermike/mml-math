/**
 * Performing test for the matrix calculations
*/
#include <mml-math/matrix.hpp>
#include <iostream>
#include <mml.hpp>


int main() {

	
	std::cout << "╭─────────────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for matrix calculations │" << std::endl;
	std::cout << "╰─────────────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

 	mml::matrix::matrix mat1(3,3);
	mat1(0,0) = 1.0;
	std::cout << "The output should be a matrix where only the element (0,0) has the value 1:" << std::endl;
	mat1.print();

	mml::matrix::matrix mat2("[[1,0,0],[0,1,0],[0,0,1]]");
	mml::matrix::matrix mat3("[[2,0,0],[0,3,0],[0,0,4]]");
	mat2("[[1,0,0]]");
	mml::matrix::matrix mat33("[[20,0,0],[100,3,0],[1000,0,4]]");

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	mml::matrix::matrix mat4 = mat2*mat33;
	
	std::cout << "The output should be the multiplication of two matrices:" << std::endl;
	mml::matrix::print_3matrix(mat2," * ",mat33, " = ", mat4);

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	mml::matrix::matrix mat5("[[3,2,0],[1,1,1],[1,2,3]]");
	mat5.print();
	double det = mat5.det();
	std::cout << "The determinant of the matrix is " << det << "." << std::endl;
	std::cout << "Is the result -1? ";
	if(det == -1.0)
		std::cout << "Yes! Test passed" <<std::endl;
	else
		std::cout << "No! There might be a bug. Please report it!" << std::endl;
	
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	
	

	std::cout << "Testing Matrix Calculation ..." << std::endl;
	mat1 = (std::string) "[[1,0,0],[3,6,3],[6,6,3]]";
	mat2 = (std::string) "[[1,0,0],[0,2,1],[3,2,1]]";
	mml::matrix::matrix res = mml::matrix::calc("[[1,0,0],[3,6,3],[6,6,3]]-[[1,0,0],[0,2,1],[3,2,1]]*[[1,0,0],[0,2,1],[3,2,1]]");
	std::cout << "The result should be a zero matrix." << std::endl;
	mml::matrix::print_4matrix(mat1, " - ", mat2, " * ", mat3, " = ", res);

	bool all_zero = true;
	for(uint32_t i = 0; i < res.rows; i++) {
		for(uint32_t j = 0; j < res.cols; j++) {
			if(res(i,j) != 0.0) {
				all_zero = false;
				break;
			}
		}
	}
	if(all_zero)
		std::cout << "Yes, the result is a zero matrix. Test passed." << std::endl;
	else
		std::cout << "No, the result is not a zero matrix! There might be a bug. Please report it!" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return 0;



}

