/**
 * @file mml-math.hpp
 * @author Mike Moser
 * @brief Includes all header files from this library
 * @version 1.0
 * @date 2024-08-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#if __GNUC__
#if __x86_64__ || __ppc64__
#define __ENVIRONMENT64__
#else
#define __ENVIRONMENT32__
#endif
#endif

#ifndef MML_MATH_INCLUDE_MML_MATH_HPP
#define MML_MATH_INCLUDE_MML_MATH_HPP

#include "mml-math/constants.hpp"
#include "mml-math/functions.hpp"
#include "mml-math/matrix.hpp"
#include "mml-math/shunting_yard_algorithm.hpp"

#endif
