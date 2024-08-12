/**
 * @author Mike Moser
 * @file matrix.hpp
 * @brief Matrix with calculations 
 * 
*/


// TODO Matrixnorm
// TODO verbose output for debugging

#ifndef mml_math_include_mml_math_matrix_hpp
#define mml_math_include_mml_math_matrix_hpp

#include <mml.hpp>
#include <vector>

namespace mml {
	namespace math {
		class matrix{ 
		
		protected:
			mml::vector<mml::vector<double>> data = {{}};
			
			/**
			 * @note Add a matrix from the right side
			 * @param matrix Matrix which is added
			 * @return result
			 * @author Mike Moser
			 * @throw runtime_error : if rows or cols are not equal
			 */
			mml::vector<mml::vector<double>> add(mml::math::matrix matrix);

			/**
		 	* @note Multiply this matrix with another one from the right side
		 	* @param matrix Matrix which is multiplied
		 	* @return new matrix
		 	* @author Mike Moser
		 	*/
			mml::vector<mml::vector<double>> multiply(mml::math::matrix matrix);

			/**
		 	* @note Multiply this matrix with a scalar
		 	* @param double Value which is multiplied to each element
		 	* @return new matrix
		 	* @author Mike Moser
		 	*/
			mml::vector<mml::vector<double>> multiply(double scalar);

			/**
			 * @note Subtract a matrix from the right side
			 * @param matrix Matrix which is subtracted
			 * @return result
			 * @author Mike Moser
			 * @throw runtime_error : if rows or cols are not equal
			 */
			mml::vector<mml::vector<double>> sub(mml::math::matrix matrix);

		public:
			std::size_t rows = 0;
			std::size_t cols = 0;

			matrix() {};
			/**
			 * @brief Initialise empty matrix with a specific form
			 * @param rows Number of rows
			 * @param cols Number of columns
			 * @return Instance of the class
			*/
	    	matrix(std::size_t rows1, std::size_t cols1) : rows(rows1), cols(cols1) {
				this->data = mml::vector<mml::vector<double>>(rows, mml::vector<double>(cols,0.0));
			}

			/**
			 * @brief Initialise matrix with a 1D vector.
			 * @param vector 1D Vector
			 * @return Instance of the class
			*/
			matrix(std::vector<double>  vec) : rows(vec.size()), cols(1) {
				this->data = mml::vector<mml::vector<double>>(rows, mml::vector<double>(cols,0.0));
				// Assign data from the 1D vector
				for(std::size_t i = 0; i < rows; i++) {
					this->data[i][0] = vec[i];
				}

			}

			/**
			 * @brief Initialise matrix with a 2D vector.
			 * @param vector 2D Vector
			 * @return Instance of the class
			*/
			matrix(mml::vector<mml::vector<double>>  vec) : data(vec), rows(vec.size()), cols(vec[0].size()) {}

			/**
			 * @note Initialise matrix with a string. E.g. like this: [[1,1],[1,1]] 
			 * @param string Values as a string
			 * @return Instance of the class with the values from the string
			 * @author Mike Moser
			*/
			matrix(std::string str1) : rows(0), cols(0) {
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

			/**
			 * @brief Assign the matrix with a 2D vector
			 * @param vector<vector> 2D vector
			 * @return Class instance
			 * @author Mike Moser
			*/
			mml::math::matrix& operator=(mml::vector<mml::vector<double>> temp) {data = temp; cols=temp[0].size(); rows = temp.size(); return *this;}

			/**
			 * @brief Assign the values with another class instance
			 * @param matrix 
			 * @return Class instance
			 * @author Mike Moser
			*/
			mml::math::matrix& operator=(mml::math::matrix temp) {data = temp.vec(); rows = temp.rows; cols = temp.cols; return *this;}

			/**
			 * @note Initialise matrix with a string. E.g. like this: [[1,1],[1,1]] 
			 * @param str1 Values
			 * @return Instance of the class with the values from the string
			 * @note that only forms of strings are usable
			 * @author Mike Moser
			*/
			mml::math::matrix& operator=(std::string str1);
			
			/**
			 * @brief Return an element of the matrix
			 * @param size_t row number
			 * @param size_t column number
			 * @return Element (i,j) from the matrix
			 * @author Mike Moser
			*/
			double& operator()(std::size_t i, std::size_t j) {return this->data[i][j];}

			/**
			 * @brief Assign a new string to the class instance
			 * @param str1 String with the new data in the format [[],[]]
			 * @return None
			 * @author Mike Moser
			*/
			void operator()(std::string str1);

			/**
		 	 * @brief Multiply this matrix with a 2D vector from the right side
		 	 * @param vector 2D vector to be multiplied
		 	 * @return New matrix
		 	 */
			mml::math::matrix operator*(mml::vector<mml::vector<double>> vec) {return multiply(mml::math::matrix(vec));}

			/**
		 	 * @brief Multiply this matrix with another one from the right side
		 	 * @param matrix Matrix to be multiplied
		 	 * @return New matrix
		 	 */
			mml::math::matrix operator*(mml::math::matrix matrix) {return multiply(matrix);}
			
			/**
		 	 * @brief Multiply this matrix with another one from the right side to this instance
		 	 * @param vec Vector to be multiplied
		 	 * @return copy of this instance
		 	 */
			mml::math::matrix& operator*=(mml::vector<mml::vector<double>> vec) {data = multiply(mml::math::matrix(vec)); return *this;}

			/**
		 	 * @brief Multiply this matrix with another one from the right side to this instance
		 	 * @param matrix Matrix to be multiplied
		 	 * @return Copy of this instance
		 	 */
			mml::math::matrix& operator*=(mml::math::matrix matrix) {data = multiply(matrix); return *this;}
	
			/**
		 	 * @brief Multiply this matrix with a scalar
		 	 * @param scalar Scalar
		 	 * @return new matrix
		 	 */
			mml::math::matrix operator*(double scalar) {return multiply(scalar);}
			
			/**
		 	 * @brief Multiply this matrix with a scalar to this instance
		 	 * @param scalar Scalar
		 	 * @return this instance
		 	 */
			mml::math::matrix& operator*=(double scalar) {data = multiply(scalar); return *this;}

			/**
		 	 * @brief Add a 2D vector from the right side
		 	 * @param vec 2D vector to be added
		 	 * @return New matrix
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator+(mml::vector<mml::vector<double>> vector){return add(mml::math::matrix(vector));}

			/**
		 	 * @brief Add another matrix from the right side
		 	 * @param matrix Matrix to be added
		 	 * @return New matrix
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator+(mml::math::matrix matrix){return add(matrix);}

			/**
		 	 * @brief Add another matrix from the right side to this instance
		 	 * @param vec Vector to be added
		 	 * @return this instance
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator+=(mml::vector<mml::vector<double>> vec){data = add(mml::math::matrix(vec)); return *this;}

			/**
		 	 * @brief Add another matrix from the right side to this instance
		 	 * @param matrix Matrix to be added
		 	 * @return this instance
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator+=(mml::math::matrix matrix){data = add(matrix); return *this;}

			/**
		 	 * @brief Subtract a 2D vector from this one from the right side
		 	 * @param vec 2D vector to be substracted
		 	 * @return New matrix
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator-(mml::vector<mml::vector<double>> vec){return sub(mml::math::matrix(vec));}

			/**
		 	 * @brief Subtract another matrix from this one from the right side
		 	 * @param matrix Matrix to be substracted
		 	 * @return New matrix
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator-(mml::math::matrix matrix){return sub(matrix);}
			
			/**
		 	 * @brief Subtract another matrix from this one from the right side to this instance
		 	 * @param vec 2D vector to be substracted
		 	 * @return this instance
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator-=(mml::vector<mml::vector<double>> vec){data = sub(mml::math::matrix(vec)); return *this;}

			/**
		 	 * @brief Subtract another matrix from this one from the right side to this instance
		 	 * @param matrix Matrix to be substracted
		 	 * @return this instance
			 * @throw runtime_error : if rows or cols are not equal
		 	 */
			mml::math::matrix operator-=(mml::math::matrix matrix){data = sub(matrix); return *this;}

			/**
		 	 * @brief Check if two matrices are the same
		 	 * @param matrix Matrix to be checked
		 	 * @return true if the same
		 	 */
			bool operator==(const mml::math::matrix matrix) const noexcept{
				return data == matrix.data;
			}

			/**
		 	 * @brief Check if two matrices are not the same
		 	 * @param matrix Matrix to be checked
		 	 * @return true if the same
		 	 */
			bool operator!=(const mml::math::matrix matrix) const noexcept{
				return data != matrix.data;
			}

			/**
			 * @brief Compute the adjugate matrix
			 * @return result
		 	*/
			mml::math::matrix adjugate() const;

			/**
			 * @brief Perform Gauss algorithm
			 * @return matrix in Gauss form
			*/
			mml::math::matrix gauss() const;

			/**
			 * @brief Compute Inverse
			 * @return Inverse Matrix
			 */
			mml::math::matrix inverse() const;
			
			/**
			 * @brief Compute determinant of the matrix
			 * @return double 
			 * @throw logic_error : if rows != cols
			 */
			double det() const;
			

			/**
			 * @brief Print the matrix in a nice-looking format
			*/
			void print() noexcept;
			
			/**
			 * @brief Matrix without a specific row and column
			 * @param row to be removed
			 * @param column to be removed
			 * @return Reduced matrix
			 * @throw runtime_error : if row or column exceeds the matrix
			 */
			mml::math::matrix reduce(uint32_t row, uint32_t column) const;

			/**
			 * @brief Summed matrix
			 * @return Sum of the matrix
			 */
			double sum() const noexcept;

			/**
			 * @brief Matrix transposed
			 * @return transposed matrix
			 */
			mml::math::matrix transpose() const noexcept;

			/**
			 * @brief Get the vector from this class
			 * @return 2D vector
			*/
			mml::vector<mml::vector<double>> vec() {return data;}
			
		};
		
		/**
		 * @brief Calculations of matrices
		 * @param equation Equation to be calculated
		 * @param verbose Verbose output, optional
		 * @return Matrix result
		 * @throw logic_error : if operator not defined or format wrong
		*/
		mml::vector<mml::vector<double>> matrix_calc(mml::string equation, bool verbose = false);

		/**
		 * @brief Print two matrices with a string inbetween
		 * @param mat1 First Matrix
		 * @param add String between the two matrices
		 * @param mat2 Second Matrix
		 * @author Mike Moser
		*/
		void print_2matrix(mml::math::matrix mat1, std::string add, mml::math::matrix mat2);

		/**
		 * @brief Print three matrices with strings inbetween
		 * @param mat1 First Matrix
		 * @param add1 String between the matrices 1 and 2
		 * @param mat2 Second Matrix
		 * @param add2 String between the matrices 2 and 3
		 * @param mat3 Third Matrix
		 
		*/
		void print_3matrix(mml::math::matrix mat1, std::string add1, mml::math::matrix mat2, std::string add2, mml::math::matrix mat3);

		/**
		 * @brief Print two matrices with a string inbetween
		 * @param mat1 First Matrix
		 * @param add1 String between the matrices 1 and 2
		 * @param mat2 Second Matrix
		 * @param add2 String between the matrices 2 and 3
		 * @param mat3 Third Matrix
		 * @param add3 String between the matrices 3 and 4
		 * @param mat4 Fourth Matrix
		*/
		void print_4matrix(mml::math::matrix mat1, std::string add1, mml::math::matrix mat2, std::string add2, mml::math::matrix mat3, std::string add3, mml::math::matrix mat4);

		/**
		 * @brief Implement a (nxn) unity matrix
		 * @param n Number or rows and columns
		 * @return mml::math::matrix
		*/
		mml::math::matrix unity(std::size_t n);
	}
	
}



#endif // mml__math__matrix_hpp
