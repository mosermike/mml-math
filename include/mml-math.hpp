/**
 * @author Mike Moser
 * @file math.hpp
 * @brief Mathematical functions
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

//#include "mml-math/derivate.hpp"
#include "mml-math/functions.hpp"
#include "mml-math/logging.hpp"
#include "mml-math/matrix.hpp"
#include "mml-math/shunting_yard_algorithm.hpp"

#endif
