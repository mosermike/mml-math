/**
 * @author Mike Moser
 * 
 * @file matrix.hpp
 * 
 * @note Matrix with calculations 
 * 
*/

#ifndef mml_math_matrix_hpp
#define mml_math_matrix_hpp

#include <mml.hpp>
#include <vector>

namespace mml {
	namespace math {
		class matrix{ 
		
		private:
			mml::vector<mml::vector<double>> data = {{0.0f}};
			
			/**
			 * @note Add a matrix from the right side
			 * @param matrix Matrix which is added
			 * @return result
			 * @author Mike Moser
			 */
			mml::math::matrix add(mml::math::matrix matrix);

			/**
		 	* @note Multiply this matrix with another one from the right side
		 	* @param matrix Matrix which is multiplied
		 	* @return new matrix
		 	* @author Mike Moser
		 	*/
			mml::math::matrix multiply(mml::math::matrix matrix);

			/**
		 	* @note Multiply this matrix with a scalar
		 	* @param double Value which is multiplied to each element
		 	* @return new matrix
		 	* @author Mike Moser
		 	*/
			mml::math::matrix multiply(double scalar);

			/**
			 * @note Subtract a matrix from the right side
			 * @param matrix Matrix which is subtracted
			 * @return result
			 * @author Mike Moser
			 */
			mml::math::matrix sub(mml::math::matrix matrix);

		public:
			std::size_t rows = 0;
			std::size_t cols = 0;
			// Constructor to initialize the matrix with given dimensions
	    	matrix(std::size_t r, std::size_t c) : rows(r), cols(c) {
				this->data = mml::vector<mml::vector<double>>(r, mml::vector<double>(c,0.0));
			}

			/**
			 * @note Initialise matrix with a string. E.g. like this: [[1,1],[1,1]] 
			 * @param string Values as a string
			 * @return Instance of the class with the values from the string
			 * @author Mike Moser
			*/
			matrix(std::string str1) {
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

			// Constructor with = a 2D vector
			matrix(mml::vector<mml::vector<double>> temp) : data(temp), rows(temp.size()), cols(temp[0].size()){};

			/**
			 * @note Assign the matrix with a 2D vector
			 * @param vector<vector> 2D vector
			 * @return Class instance
			 * @author Mike Moser
			*/
			mml::math::matrix& operator=(mml::vector<mml::vector<double>> temp) {data = temp; cols=temp[0].size(); rows = temp.size(); return *this;}

			/**
			 * @note Assign the values with another class instance
			 * @param matrix 
			 * @return Class instance
			 * @author Mike Moser
			*/
			mml::math::matrix& operator=(mml::math::matrix temp) {data = temp.get_vec(); rows = temp.rows; cols = temp.cols; return *this;}

			/**
			 * @note Return an element of the matrix
			 * @param size_t row number
			 * @param size_t column number
			 * @return Element (i,j) from the matrix
			 * @author Mike Moser
			*/
			double& operator()(std::size_t i, std::size_t j) {return this->data[i][j];}

			/**
			 * @note Assign a new string to the class instance
			 * @param string String with the new data in the format [[],[]]
			 * @return None
			 * @author Mike Moser
			*/
			void operator()(std::string str1);

			/**
		 	* @note Multiply this matrix with another one from the right side
		 	* @param matrix Matrix to be multiplied
		 	* @return New matrix
		 	* @author Mike Moser
		 	*/
			mml::math::matrix operator*(mml::math::matrix matrix) {return multiply(matrix);}
			mml::math::matrix operator*=(mml::math::matrix matrix) {data = multiply(matrix).get_vec(); return *this;}

			/**
		 	* @note Multiply this matrix with a scalar
		 	* @param double Scalar
		 	* @return new matrix
		 	* @author Mike Moser
		 	*/
			mml::math::matrix operator*(double scalar) {return multiply(scalar);}

			/**
		 	* @note Add another matrix from the right side
		 	* @param matrix Matrix to be added
		 	* @return New matrix
		 	* @author Mike Moser
		 	*/
			mml::math::matrix operator+(mml::math::matrix matrix){return add(matrix);}

			/**
		 	* @note Subtract another matrix from this one from the right side
		 	* @param matrix Matrix to be substracted
		 	* @return New matrix
		 	* @author Mike Moser
		 	*/
			mml::math::matrix operator-(mml::math::matrix matrix){return sub(matrix);}

			/**
			 * @note Compute the adjugate matrix
			 * 
			 * @return result
			 * @author Mike
		 	*/
			mml::math::matrix adjugate();
		
			/**
			 * @note Get the vector from this class
			 * @return vector
			 * @author Mike Moser
			*/
			mml::vector<mml::vector<double>> get_vec() {return data;}

			/**
			 * @note Perform Gauss algorithm
			 * @return matrix
			 * @author Mike Moser
			*/
			mml::math::matrix gauss();

			/**
			 * @note Compute Inverse
			 * 
			 * @return Inverse Matrix
			 * @author Mike
			 */
			mml::math::matrix inverse();

			/**
			 * @note Compute determinant of the matrix
			 * 
			 * @return double 
			 * @author Mike Moser
			 */
			double det();
			

			/**
			 * @note Print the matrix in a nice-looking format
			 * @author Mike Moser
			*/
			void print();
			
			/**
			 * @note Matrix without a specific row and column
			 * 
			 * @return reduced matrix
			 * @author Mike
			 */
			mml::math::matrix reduce(uint32_t row, uint32_t column);
			/**
			 * @note Matrix transposed
			 * 
			 * @return transposed matrix
			 * @author Mike
			 */
			mml::math::matrix transpose();
			
		};
		
		/**
		 * @note Print two matrices with a string inbetween
		 * @param matrix First Matrix
		 * @param string String between the two matrices
		 * @param matrix Second Matrix
		 * @author Mike Moser
		*/
		void print_2matrix(mml::math::matrix mat1, std::string add, mml::math::matrix mat2);
		/**
		 * @note Print two matrices with a string inbetween
		 * @param matrix First Matrix
		 * @param matrix Second Matrix
		 * @param string String between the two matrices
		*/
		void print_3matrix(mml::math::matrix mat1, std::string add1, mml::math::matrix mat2, std::string add2, mml::math::matrix mat3);
	}
	
}



#endif // mml__math__matrix_hpp
