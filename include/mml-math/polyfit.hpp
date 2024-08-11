/**
 * @author Mike Moser
 * @file polyfit.hpp
 * @brief Function for fitting a polynomial
 * 
*/

#ifndef mml_math_include_mml_math_polyfit_hpp
#define mml_math_include_mml_math_polyfit_hpp

#include <mml.hpp>
#include "matrix.hpp"

namespace mml {
	namespace math {
		/**
		 * @brief Class to perform a polynomial fit.
		 * @cite The Elements of Statistical Learning by Trevor Hastie, Robert Tibshirani and Jerome Friedman
		 */
		class polyfit {
		private:
			mml::math::matrix X;
			std::vector<double> x;
			std::vector<double> y;
		public:
			std::size_t degree = 0;	
			mml::math::matrix coeff; // Coefficients of the fit. Start from the smallest degree.
			mml::math::matrix covar;

			/**
			 * @brief Initialise the polynomial fit by determining the x and y data as well as the degree of the polynomial fit
			 * @param x Data in x
			 * @param y Data in y
			 * @param deg Degree of the polynom to be fitted
			 */
			polyfit(std::vector<double> x, std::vector<double> y, std::size_t deg) : x(x), y(y), degree(deg), coeff(mml::math::matrix(deg, 1)) {
				X = mml::math::matrix(x.size(),deg+1);
				// Assign 1 to the first column
				for(std::size_t i = 0; i < X.rows; i++)
					X(i,0) = 1.0;

				// Assign x to each row starting from position 1
				for(std::size_t row = 0; row < X.rows; row++) {
					for(std::size_t col = 0; col < X.cols; col++)
						X(row,col) = std::pow(x[row],col);
				}
			}

			/**
			 * @brief Perform the fit by using the equation
			 * 			$$ \\beta = \\left[\\left(X^{T}\\cdot x\\right)^{-1} \\cdot X^{T}\right] \\csdot y $$
			 * @param cov Compute covariance of the fit. Default: false
			 * @return Computed coefficients for the equation $y = a_1 + a_2 \\cdot x + a_3 \\cdot x^2 + ...$.
			 * @cite The Elements of Statistical Learning by Trevor Hastie, Robert Tibshirani and Jerome Friedman
			 */
			mml::math::matrix fit(bool cov = false) {
				coeff = ((X.transpose()*X).inverse()*X.transpose())*y;
				// Correct for very small numbers if average of y is big => 1e-15 = 0
				double average = std::accumulate(y.begin(), y.end(), 0.0) / y.size();
				if (average > 1e-8) {
					for(std::size_t row = 0; row < degree+1; row++)
						coeff(row,0) = (abs(coeff(row,0)) < 1e-10) ? 0.0 : coeff(row,0);
				}

				// Correct for -0
				for(std::size_t row = 0; row < degree+1; row++)
					coeff(row,0) = (abs(coeff(row,0)) == 0.0) ? 0.0 : coeff(row,0);

				if(cov)
					covariance_matrix();
				return coeff;
			}

			/**
			 * @brief Compute the covariance matrix
			 * @return Covariance matrix of the fit
			 * @details The equation to be computed is $$(X^{T}X)^{-1}\\cdot \\sigma^2$$
			 * 			with $$\\sigma^2 = \\frac{1}{N-degree-1} \\sum_{i=1}^{N}(y_i-\\hat{y_i})^2.$$
			 * @cite The Elements of Statistical Learning by Trevor Hastie, Robert Tibshirani and Jerome Friedman
			 */
			mml::math::matrix covariance_matrix() {
				if(x.size() <= degree+1) {
					std::length_error("[covariance_matrix] The number of data points must exceed order to scale the covariance matrix");
				}
				// Compute the predicted values
				std::vector<double> y_pred;
				y_pred.reserve(x.size());

				for (std::size_t i = 0; i < x.size(); i++) {
					double y_value = coeff(0,0);
					for (std::size_t j = 1; j < degree+1; j++) {
						y_value += coeff(j, 0) * std::pow(x[i], j);
					}
					y_pred.push_back(y_value);
				}

				// Compute the residuals
				double residual_sum_of_squares = 0.0;
				for (std::size_t i = 0; i < y.size(); i++) {
					residual_sum_of_squares += std::pow(y[i] - y_pred[i], 2);
				}

				// Compute the variance of the residuals
				double sigma_squared = residual_sum_of_squares / (x.size() - (degree + 1));
				std::cout << sigma_squared << std::endl;
				// Compute the covariance matrix
				covar = (X.transpose() * X).inverse()  * sigma_squared;

				return covar;
			}
		};
		
		
	}
}
#endif
