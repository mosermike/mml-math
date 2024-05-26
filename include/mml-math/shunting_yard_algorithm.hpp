/**
 * @brief Shunting Yard Algorithm
 * @cite https://en.wikipedia.org/wiki/Shunting_yard_algorithm
 * @author Mike Moser
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <mml/standards.hpp>
#include <mml/vector.hpp>

// TODO look at logb

#ifndef mml_math_shunting_yard_hpp
#define mml_math_shunting_yard_hpp

namespace mml {
    namespace math {
        class shunting_yard_algorithm {
            private:
            // Structure for the functions map with the range and the function
            struct FunctionInfo {
                double min = 0;
                double max = 0;
                std::function<double(double)> func = [](double x) { return x;};
            };
            protected:
            // Maps of recognized functions with their corresponding implementations
            std::unordered_map<std::string, FunctionInfo> functions = {
                {"exp",{-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), [](double x) { return std::exp(x); }}},
                {"log10",{0, std::numeric_limits<double>::infinity(), [](double x) { return std::log10(x); }}},
                {"ln",{0, std::numeric_limits<double>::infinity(), [](double x) { return std::log(x); }}},
                {"sqrt",{0, std::numeric_limits<double>::infinity(), [](double x) { return std::sqrt(x); }}},
                {"sin",{0, 2*M_PI, [](double x) { return std::sin(x); }}},
                {"cos",{0, 2*M_PI, [](double x) { return std::cos(x); }}},
                {"tan",{0, 2*M_PI, [](double x) { return std::tan(x); }}},
                {"asin",{-1, 1, [](double x) { return std::asin(x); }}},
                {"acos",{-1, 1, [](double x) { return std::acos(x); }}},
                {"atan",{-1, 1, [](double x) { return std::atan(x); }}},
            };

            public:
            mml::string equation = "";
            std::vector<mml::string> infix = {};
            std::vector<mml::string> postfix = {};
            double result = 0.0;

            shunting_yard_algorithm(mml::string equation) : equation(equation) {};
            shunting_yard_algorithm(std::vector<mml::string> infix) : infix(infix) {for(mml::string i : infix) {equation += i;}};
            shunting_yard_algorithm() {};

            /**
             * @brief Assign the class with an equation
             * @param equation
             * @return Instance of the class
            */
            shunting_yard_algorithm& operator=(mml::string equation) {
                this->equation = equation;
                return *this;
            }

            /**
             * @brief Converts a string to tokens where numbers are kept together and spaces are ignored
             * @param verbose Verbose output (optional)
             * @return Vector filled with the tokens
             * @throw runtime_error : if equation is empty
             * @throw invalid_argument : if unrecognized function or variable
            */
            std::vector<mml::string> equation_to_infix(bool verbose = false);

            /**
             * @brief Converts infix to postfix notation
             *        E.g.: '2+3' is converted to '23+'
             * @param verbose Verbose output (optional)
             * @return Vector filled with the tokens
             * @throw runtime_error : if infix is empty
            */
            std::vector<mml::string> infix_to_postfix(bool verbose = false);
            
            protected:
            /**
             * @brief Returns the precedence of an operator: The higher the more precedent (* has higher precendence than +)
             * @param op Operator
             * @param int
            */
            int precedence(mml::string op) noexcept;
            
            public:

            /**
             * @brief Evaluates the postfix vector
             * @param verbose Verbose output (optional)
             * @return double
             * @throw out_of_range : if value is out of range of a function
            */
            double evaluate_postfix(bool verbose = false);

            /**
             * @brief Evaluates the string and returns the result
             * @param verbose Verbose output (optional)
             * @return double
            */
            double evaluate(bool verbose = false);
        };
    }
}

#endif




