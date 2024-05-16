/**
 * @author Mike Moser
 * 
 * @file math.hpp
 * @note Enthält verschiedene mathematische Funktionen
 * 
*/


#pragma once

#if __GNUC__
#if __x86_64__ || __ppc64__
#define __ENVIRONMENT64__
#else
#define __ENVIRONMENT32__
#endif
#endif

#ifndef __MML_MATH_HPP__
#define __MML_MATH_HPP__

namespace mml{
	namespace rechner{
		extern double calculate(mml::shell::arg args, mml::string equation, bool replace);
	}
}
#include "mml-math/basic_operations.hpp"
#include "mml-math/derivate.hpp"
#include "mml-math/functions.hpp"
#include "mml-math/logging.hpp"
#include "mml-math/matrix.hpp"

#endif
