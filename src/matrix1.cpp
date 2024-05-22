#include <mml.hpp>
#include "../include/mml-math/matrix1.hpp"

mml::math::matrix mml::math::matrix::add(mml::math::matrix mat) {
	
	mml::math::matrix res(rows,cols);

	// ===============================
	// Check if addition is possible
	// ===============================
	if(rows != mat.rows) {
		mml::shell::warn_opt("[matrix::add] Number of rows different (" + std::to_string(rows) + " vs. " + std::to_string(mat.rows) + ")!");
		return res;
	}
	if(cols != mat.cols) {
		mml::shell::warn_opt("[matrix::add] Number of columns different (" + std::to_string(cols) + " vs. " + std::to_string(mat.cols) + ")!");
		return res;
	}

	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < cols; j++)  {
			res(i,j) = data[i][j] + mat(i,j);
		}
	}
	
	return res;	
}


mml::math::matrix mml::math::matrix::adjugate() {
	
	mml::math::matrix adj(rows,cols);
	
	mml::math::matrix temp(rows-1,cols-1);
	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < cols; j++) {
			temp = reduce(i,j);
			adj(i,j) = (std::pow(-1,i+j+2)) * (temp.det());
		}
	}

	return adj.transpose();
}


double mml::math::matrix::det() {
	double determinant = 1;
	
	// ===============================
	// Check if determinant is defined
	// ===============================
	if(cols != rows)
		mml::shell::warn("| Determinant not defined!");	
	
	// Check if one column is 0
	for (uint16_t i = 0; i < rows; i++) {
		bool zero_line = true;
		for (uint16_t j = 0; j < cols; j++) {
			if(data[i][j] > 1e-8  || data[i][j] < -1e-8) {
				zero_line = false;
				break;
			}
		}
		if (zero_line) {
			return 0.0;
		}
	}
	
	// Check if one row is 0
	for (uint16_t j = 0; j < cols; j++) {
		bool zero_line = true;
		for (uint16_t i = 0; i < rows; i++) {
			if(data[i][j] > 1e-8 || data[i][j] < -1e-8) {
				zero_line = false;
				break;
			}
		}
		if (zero_line) {
			return 0.0;
		}
	}
	
	// =================
	// Gauß-Algorithm:
	// =================
	// Go through all rows
	matrix temp(data);
	for(uint32_t n = 0; n < rows; n++) {
		// Eine Zeilenberechnung:
		for(uint32_t i = n; i < rows-1; i++) {

			// Swap two columns so that there is no division by 0
			if(temp(n,n) == 0.0) {
				int m = n+1;
				determinant = determinant * (-1); // => Swap results into different det.
				do {
					// start from the start if m bigger than rows
					if (m >= (int) rows)
						m = 0;

					// Vertauschen durchführen, falls Bedingung stimmt:
					if(abs(temp(m,n)) > 1e-50) {
						for(uint32_t m1 = 0; m1 < cols; m1++) {
							std::swap(temp(n,m1),temp(m,m1));
						}
					}
					else
						m++;
				} while(abs(temp(n,n)) < 1e-50);
			}
			
			double faktor = temp(i+1,n)/temp(n,n);
			
			for(uint32_t j = 0; j < cols; j++) {
				temp(i+1,j) = temp(i+1,j)-(faktor*temp(n,j));
			}
		}
	}
			
	// =========================================
	// Compute determinant from diagonal entries
	// =========================================
	for(uint32_t i = 0; i < rows; i++)
		determinant *= temp(i,i);
	
	return determinant;
}

mml::math::matrix mml::math::matrix::inverse() {
	
	// Compute determinant as needed later
	double Det = det();
	if(Det == 0) {
		std::cout << "[inverse] Inverse not defined. Matrix is singular (det = 0)" << std::endl;
		return *this;
	}
	
	// ===================
	// Compute adjugate:
	// ===================
	matrix adj = adjugate();
		
	// ===============
	// Compute Inverse
	// ===============
	matrix inv(rows,cols);
	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < cols; j++) {
			inv(i,j) = (1/Det) * (adj(i,j));
		}
	}
	
	return inv;
}



mml::math::matrix mml::math::matrix::multiply(mml::math::matrix mat) {
	
	// ===================================
	// Check if multiplication is possible
	// ===================================
	if(cols != mat.rows)
		mml::shell::warn("| Multiplication not possible!");	
	
	mml::math::matrix res(rows,mat.cols);
	
	
	// =====================
	// Matrix multiplication
	// =====================
	for(uint32_t m = 0; m < rows; m++) {
		for(uint32_t n = 0; n < mat.cols; n++) {
			double temp_d = 0;
			for(uint32_t i = 0; i < mat.rows; i++) {
					temp_d += data[m][i]*mat(i,n);
			}
			res(m,n) = temp_d;
		}
	}
	
	return res;
}

mml::math::matrix mml::math::matrix::multiply(double scalar) {
	
	mml::math::matrix res(rows,cols);
	
	
	// =====================
	// Matrix multiplication
	// =====================
	for(uint32_t m = 0; m < rows; m++) {
		for(uint32_t n = 0; n < cols; n++) {
			res(m,n) = data[m][n]*scalar;
		}
	}
	
	return res;
}

void mml::math::matrix::operator()(std::string str1) {
	// Change to mml::string
	mml::string str(str1);
	// Perform some checks for the format
	if(str.sub(0,1) != "[[") {
		mml::shell::warn_opt("[matrix] String does not start with [[. Check the format!");
		return;
	}
	else if(str.sub(-2,-1) != "]]") {
		mml::shell::warn_opt("[matrix] String does not end with ]]. Check the format!");
		return;
	}
				
	// Determine Number of rows == Number of [
	rows = 0;
	cols = 0;
	for(uint32_t i = 1; i < str.size(); i++) {
		if(str[i] == '[')
			rows++;
		}
		// Determine number of columns from first row
		mml::string temp = str.sub(1,str.find(']'));
		cols++; // First entry is not count
		for(uint32_t i = 0; i < temp.size(); i++) {
			if(temp[i] == ',')
				cols++;
		}

		// Initialise 2D vector
		this->data = mml::vector<mml::vector<double>>(rows, mml::vector<double>(cols,0.0));
				
		// Remove first [ and last ]
		str = str.sub(1,-2);

		// Assign the value
		for(uint32_t i = 0; i < rows; i++) {
			// Find the first row
			std::size_t temp1	= str.find('[');
			std::size_t temp2	= str.find(']');
					
			// Extract the row and remove it from the string
			temp	= str.sub(temp1+1,temp2-1);
			str = str.substr(temp2+1);

			// Go through the extracted row and assign by column
			for(uint32_t j = 0; j < cols; j++) {
				// Cut out the string to the next , and store it and remove this part from the string
				if(temp.exist(",")) {
					data[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
					temp = temp.substr(temp.find(',')+1);
				}
				// If last ',' removed, assign last value
				else
		data[i][j] = temp.atof();
	}
}

}


void mml::math::matrix::print() {

	// ===================================
	// Determine Length of biggest numbers
	// ===================================
	uint32_t digit1[cols] = {0};
	
	for(uint32_t i = 0; i < cols; i++) {
		for(uint32_t n = 0; n < rows; n++) {
			if(mml::functions::digits(data[n][i]) > digit1[i])
				digit1[i] = mml::functions::digits(data[n][i]);
		}
	}
	

	// ======================================
	// Define dimension of the printable area
	// ======================================	
	// Number of spaces between brackets
	uint32_t num_space1 = 1; // Number of spaces in each column
	for (uint32_t i = 0; i < cols; i++)
		num_space1 += digit1[i]+1;
	
	// ===============================================
	// Initialize vector and positions for each matrix
	// ===============================================

	// Create print area
	std::vector<std::vector<std::string>> print = std::vector<std::vector<std::string>>(
		rows+2,std::vector<std::string>(num_space1+2," "));

	// Start and end positions of each matrix
	std::size_t start_mat1_col = 0;
	std::size_t start_mat1_row = rows-rows;
	
	std::size_t end_mat1_col = start_mat1_col + num_space1 + 2 - 1;
	std::size_t end_mat1_row = rows+1;
	
	// =============
	// Assign values
	// =============
	// Put brackets
	print[start_mat1_row][start_mat1_col] = "╭";
	
	print[start_mat1_row][end_mat1_col] = "╮";
	
	print[end_mat1_row][start_mat1_col] = "╰";
	
	print[end_mat1_row][end_mat1_col] = "╯";
	
	// Assign values of first matrix
	for(uint32_t i = 0; i < rows; i++) {
		std::size_t skips = 0;
		
		print[start_mat1_row+1 + i][start_mat1_col] = "│";

		for(uint32_t j = 0; j < cols; j++) {
			// Correction for -0
			if(data[i][j] == -0)
				data[i][j] = 0;
			
			// Skip so many entries due to different numbers
			for(uint32_t n = mml::functions::digits(data[i][j]); n <= digit1[j]; n++) {
				skips++;
			}

			print[start_mat1_row+1 + i ][start_mat1_col+1 + j + skips] = std::to_string(data[i][j]);
		}

		// Delete all additional spaces between the bracket and the last number in a column
		for(uint32_t n = end_mat1_col-2; ; n--) {
			if(print[start_mat1_row+1 + i ][n][0] == ' ')
				print[start_mat1_row+1 + i ][n] = "";
			else
				break;
		}

		print[start_mat1_row+1 +i][end_mat1_col] = "│";
	}

	

	// Print to shell
	for(uint32_t i = 0; i < print.size(); i++) {
		for(uint32_t j = 0; j < print[0].size(); j++) {
			if(mml::is_num(print[i][j][0]) || mml::is_num(print[i][j][1]))
				std::cout << std::stof(print[i][j]);
			else
				std::cout << print[i][j];
		}
		std::cout << std::endl;
	}	
	return;

}

mml::math::matrix mml::math::matrix::reduce(uint32_t row, uint32_t column) {

	matrix red(rows-1,cols-1);	

	if(row >= rows) {
		mml::shell::warn_opt("[matrix::red] Selected row " + std::to_string(row) + " exceeds the number of rows " + std::to_string(rows) + "!");
		return red;
	}
	if(column >= cols) {
		mml::shell::warn_opt("[matrix::red] Selected column " + std::to_string(column) + " exceeds the number of columns " + std::to_string(cols) + "!");
		return red;
	}

	
	// ==============================
	// Delete selected row and column
	// ==============================
	int u = 0;
	for(uint32_t i = 0; i < rows-1; i++) {
		if(i == row) {
			u = 1;
		}
		int t = 0;
		for(uint32_t j = 0; j < cols-1; j++) {
			if(j == column) {
				t = 1;
			}
			red(i,j) = data[i+u][j+t];
		}
	}
	
	return red;
	
}

mml::math::matrix mml::math::matrix::sub(mml::math::matrix mat) {
	

	mml::math::matrix res(rows,cols);
	// ================================
	// Check if subtraction is possible
	// ================================
	if(rows != mat.rows) {
		mml::shell::warn_opt("[matrix::sub] Number of rows different (" + std::to_string(rows) + " vs. " + std::to_string(mat.rows) + ")!");
		return res;
	}
	if(cols != mat.cols) {
		mml::shell::warn_opt("[matrix::sub] Number of columns different (" + std::to_string(cols) + " vs. " + std::to_string(mat.cols) + ")!");
		return res;
	}

	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < cols; j++)  {
			res(i,j) = data[i][j] - mat(i,j);
		}
	}
	
	return res;	
}


mml::math::matrix mml::math::matrix::transpose() {

	matrix tra(cols,rows);

	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < cols; j++) {
			tra(j,i) = data[i][j];
		}
	}
	
	return tra;
	
}




void mml::math::print_2matrix(mml::math::matrix mat1, std::string add, mml::math::matrix mat2) {

	// ===================================
	// Determine Length of biggest numbers
	// ===================================
	uint32_t digit1[mat1.cols] = {0};
	uint32_t digit2[mat2.cols] = {0};
	for(uint32_t i = 0; i < mat1.cols; i++) {
		for(uint32_t n = 0; n < mat1.rows; n++) {
			if(mml::functions::digits(mat1(n,i)) > digit1[i])
				digit1[i] = mml::functions::digits(mat1(n,i));
		}
	}
	for(uint32_t i = 0; i < mat2.cols; i++) {
		for(uint32_t n = 0; n < mat2.rows; n++) {
			if(mml::functions::digits(mat2(n,i)) > digit2[i])
				digit2[i] = mml::functions::digits(mat2(n,i));
		}
	}

	// ======================================
	// Define dimension of the printable area
	// ======================================	
	// Max number of rows
	std::size_t rows = std::max(mat1.rows,mat2.rows);

	// Number of spaces between brackets
	uint32_t num_space1 = 1; // Number of spaces in each column
	for (uint32_t i = 0; i < mat1.cols; i++)
		num_space1 += digit1[i]+1;
	uint32_t num_space2 = 2; // Number of spaces in each column
	for (uint32_t i = 0; i < mat2.cols; i++)
		num_space2 += digit2[i]+1;

	// ===============================================
	// Initialize vector and positions for each matrix
	// ===============================================

	// Create print area
	std::vector<std::vector<std::string>> print = std::vector<std::vector<std::string>>(
		rows+2,std::vector<std::string>(num_space1+num_space2+2+1+add.size()," "));

	// Start and end positions of each matrix
	std::size_t start_mat1_col = 0;
	std::size_t start_mat1_row = rows-mat1.rows;
	std::size_t start_mat2_col = num_space1 + 2 + add.size();
	std::size_t start_mat2_row = rows-mat2.rows;
 
	std::size_t end_mat1_col = start_mat1_col + num_space1 + 2 - 1;
	std::size_t end_mat1_row = rows+1;
	std::size_t end_mat2_col = start_mat2_col + num_space2;
	std::size_t end_mat2_row = rows+1;

	// =============
	// Assign values
	// =============
	// Put brackets
	print[start_mat1_row][start_mat1_col] = "╭";
	print[start_mat2_row][start_mat2_col] = "╭";
	
	print[start_mat1_row][end_mat1_col] = "╮";
	print[start_mat2_row][end_mat2_col] = "╮";
	
	print[end_mat1_row][start_mat1_col] = "╰";
	print[end_mat2_row][start_mat2_col] = "╰";

	print[end_mat1_row][end_mat1_col] = "╯";
	print[end_mat2_row][end_mat2_col] = "╯";

	// Assign values of first matrix
	for(uint32_t i = 0; i < mat1.rows; i++) {
		std::size_t skips = 0;
		
		print[start_mat1_row+1 + i][start_mat1_col] = "│";

		for(uint32_t j = 0; j < mat1.cols; j++) {
			// Correction for -0
			if(mat1(i,j) == -0)
				mat1(i,j) = 0;
			
			// Skip so many entries due to different numbers
			for(uint32_t n = mml::functions::digits(mat1(i,j)); n <= digit1[j]; n++) {
				skips++;
			}

			print[start_mat1_row+1 + i ][start_mat1_col+1 + j + skips] = std::to_string(mat1(i,j));
		}

		// Delete all additional spaces between the bracket and the last number in a column
		for(uint32_t n = end_mat1_col-2; ; n--) {
			if(print[start_mat1_row+1 + i ][n][0] == ' ')
				print[start_mat1_row+1 + i ][n] = "";
			else
				break;
		}

		print[start_mat1_row+1 +i][end_mat1_col] = "│";
	}

	

	for(uint32_t i = 0; i < add.size(); i++ )
		print[((int)rows/2+0.5)+1][end_mat1_col+1 + i] =  add[i];

	// Assign values of second matrix
	for(uint32_t i = 0; i < mat2.rows; i++) {
		std::size_t skips = 0;
		
		print[start_mat2_row+1 + i][start_mat2_col] = "│";

		for(uint32_t j = 0; j < mat2.cols; j++) {
			// Correction for -0
			if(mat2(i,j) == -0)
				mat2(i,j) = 0;

			for(uint32_t n = mml::functions::digits(mat2(i,j)); n <= digit2[j]; n++) {
				skips++;
			}
			
			print[start_mat2_row+1 + i ][start_mat2_col+1 + j + skips] = std::to_string(mat2(i,j));
		}

		// Delete all additional spaces between the bracket and the last number in a column
		for(uint32_t n = end_mat2_col-2; ; n--) {
			if(print[start_mat2_row+1 + i ][n][0] == ' ')
				print[start_mat2_row+1 + i ][n] = "";
			else
				break;
		}

		
		print[start_mat2_row+1 +i][end_mat2_col] = "│";
	}

	// Print to shell
	for(uint32_t i = 0; i < print.size(); i++) {
		for(uint32_t j = 0; j < print[0].size(); j++) {
			if(mml::is_num(print[i][j][0]) || mml::is_num(print[i][j][1]))
				std::cout << std::stof(print[i][j]);
			else
				std::cout << print[i][j];
		}
		std::cout << std::endl;
	}	
	return;

}

void mml::math::print_3matrix(mml::math::matrix mat1, std::string add1, mml::math::matrix mat2, std::string add2, mml::math::matrix mat3) {

	// ===================================
	// Determine Length of biggest numbers
	// ===================================
	uint32_t digit1[mat1.cols] = {0};
	uint32_t digit2[mat2.cols] = {0};
	uint32_t digit3[mat3.cols] = {0};
	
	for(uint32_t i = 0; i < mat1.cols; i++) {
		for(uint32_t n = 0; n < mat1.rows; n++) {
			if(mml::functions::digits(mat1(n,i)) > digit1[i])
				digit1[i] = mml::functions::digits(mat1(n,i));
		}
	}

	for(uint32_t i = 0; i < mat2.cols; i++) {
		for(uint32_t n = 0; n < mat2.rows; n++) {
			if(mml::functions::digits(mat2(n,i)) > digit2[i])
				digit2[i] = mml::functions::digits(mat2(n,i));
		}
	}

	for(uint32_t i = 0; i < mat3.cols; i++) {
		for(uint32_t n = 0; n < mat3.rows; n++) {
			if(mml::functions::digits(mat3(n,i)) > digit3[i])
				digit3[i] = mml::functions::digits(mat3(n,i));
		}
	}
	
	// ======================================
	// Define dimension of the printable area
	// ======================================

	// Max number of rows
	std::size_t rows = std::max(mat1.rows,std::max(mat2.rows,mat3.rows));

	// Number of spaces between brackets
	uint32_t num_space1 = 1; // Number of spaces in each column
	for (uint32_t i = 0; i < mat1.cols; i++)
		num_space1 += digit1[i]+1;
	uint32_t num_space2 = 2; // Number of spaces in each column
	for (uint32_t i = 0; i < mat2.cols; i++)
		num_space2 += digit2[i]+1;
	uint32_t num_space3 = 2; // Number of spaces in each column
	for (uint32_t i = 0; i < mat3.cols; i++)
		num_space3 += digit3[i]+1;

	// ===============================================
	// Initialize vector and positions for each matrix
	// ===============================================
	
	// Initialize vector
	std::vector<std::vector<std::string>> print = std::vector<std::vector<std::string>>(rows+2,std::vector<std::string>(num_space1+num_space2+num_space3+2+2+add1.size()+add2.size()," "));

	// Start and end positions of each matrix
	std::size_t start_mat1_col = 0;
	std::size_t start_mat1_row = rows-mat1.rows;
	std::size_t end_mat1_col = start_mat1_col + num_space1 + 2 - 1;
	std::size_t end_mat1_row = rows+1;

	std::size_t start_mat2_col = num_space1 + 2 + add1.size();
	std::size_t start_mat2_row = rows-mat2.rows;
	std::size_t end_mat2_col = start_mat2_col + num_space2;
	std::size_t end_mat2_row = rows+1;

	std::size_t start_mat3_col = end_mat2_col + add2.size() +1; // +1 for the ending of the other
	std::size_t start_mat3_row = rows-mat3.rows;
	std::size_t end_mat3_col = start_mat3_col + num_space3;
	std::size_t end_mat3_row = rows+1;

	// =============
	// Assign values
	// =============
 	// Put brackets
	print[start_mat1_row][start_mat1_col] = "╭";
	print[start_mat2_row][start_mat2_col] = "╭";
	print[start_mat3_row][start_mat3_col] = "╭";
	
	print[start_mat1_row][end_mat1_col] = "╮";
	print[start_mat2_row][end_mat2_col] = "╮";
	print[start_mat3_row][end_mat3_col] = "╮";
	
	print[end_mat1_row][start_mat1_col] = "╰";
	print[end_mat2_row][start_mat2_col] = "╰";
	print[end_mat3_row][start_mat3_col] = "╰";

	print[end_mat1_row][end_mat1_col] = "╯";
	print[end_mat2_row][end_mat2_col] = "╯";
	print[end_mat3_row][end_mat3_col] = "╯";

	// Assign values of first matrix
	for(uint32_t i = 0; i < mat1.rows; i++) {
		std::size_t skips = 0;
		
		print[start_mat1_row+1 + i][start_mat1_col] = "│";
		for(uint32_t j = 0; j < mat1.cols; j++) {
			// Correction for -0
			if(mat1(i,j) == -0)
				mat1(i,j) = 0;
			
			for(uint32_t n = mml::functions::digits(mat1(i,j)); n <= digit1[j]; n++)
				skips++;

			print[start_mat1_row+1 + i ][start_mat1_col+1 + j + skips] = std::to_string(mat1(i,j));
			
		}
		// Delete all additional spaces between the bracket and the last number in a column
		for(uint32_t n = end_mat1_col-2; ; n--) {
			if(print[start_mat1_row+1 + i ][n][0] == ' ')
				print[start_mat1_row+1 + i ][n] = "";
			else
				break;
		}

		print[start_mat1_row+1 +i][end_mat1_col] = "│";
	}

	// Add the additional string
	for(uint32_t i = 0; i < add1.size(); i++ )
		print[((int)rows/2+0.5)+1][end_mat1_col+1 + i] =  add1[i];

	// Assign values of second matrix
	for(uint32_t i = 0; i < mat2.rows; i++) {
		std::size_t skips = 0;
		
		print[start_mat2_row+1 + i][start_mat2_col] = "│";
		for(uint32_t j = 0; j < mat2.cols; j++) {
			// Correction for -0
			if(mat2(i,j) == -0)
				mat2(i,j) = 0;
			
			for(uint32_t n = mml::functions::digits(mat2(i,j)); n <= digit2[j]; n++)
				skips++;

			print[start_mat2_row+1 + i ][start_mat2_col+1 + j + skips] = std::to_string(mat2(i,j));
			
		}
		// Delete all additional spaces between the bracket and the last number in a column
		for(uint32_t n = end_mat2_col-2; ; n--) {
			if(print[start_mat2_row+1 + i ][n][0] == ' ')
				print[start_mat2_row+1 + i ][n] = "";
			else
				break;
		}
		print[start_mat2_row+1 +i][end_mat2_col] = "│";
	}

	// Add the additional string
	for(uint32_t i = 0; i < add2.size(); i++ )
		print[((int)rows/2+0.5)+1][end_mat2_col+1 + i] =  add2[i];

	// Assign values of second matrix
	for(uint32_t i = 0; i < mat3.rows; i++) {
		std::size_t skips = 0;
		
		print[start_mat3_row+1 + i][start_mat3_col] = "│";
		for(uint32_t j = 0; j < mat3.cols; j++) {
			// Correction for -0
			if(mat3(i,j) == -0)
				mat3(i,j) = 0;
			
			for(uint32_t n = mml::functions::digits(mat3(i,j)); n <= digit3[j]; n++)
				skips++;

			print[start_mat3_row+1 + i ][start_mat3_col+1 + j + skips] = std::to_string(mat3(i,j));
			
		}
		// Delete all additional spaces between the bracket and the last number in a column
		for(uint32_t n = end_mat3_col-2; ; n--) {
			if(print[start_mat3_row+1 + i ][n][0] == ' ')
				print[start_mat3_row+1 + i ][n] = "";
			else
				break;
		}
		print[start_mat3_row+1 +i][end_mat3_col] = "│";
	}

	// Print to shell
	for(uint32_t i = 0; i < print.size(); i++) {
		for(uint32_t j = 0; j < print[0].size(); j++) {
			if(mml::is_num(print[i][j][0]) || mml::is_num(print[i][j][1]))
				std::cout << std::stof(print[i][j]);
			else
				std::cout << print[i][j];
		}
		std::cout << std::endl;
	}	
	return;

}