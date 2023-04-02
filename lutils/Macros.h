/**
 * \file Macros.h
 * \brief
 *
 * Useful macros - utils
 *
 * \version 1.0.0
 * \date 03/03/2023
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#pragma once

#if defined(_MSC_VER)
#	define LRESTRICT __restrict
#	define LFORCEINLINE __forceinline
#	define LFORCEINLINE_LAMBDA [[msvc::forceinline]]
#elif defined(__clang__) || defined(__GNUC__)
#	define LRESTRICT __restrict__
#	define LFORCEINLINE inline __attribute__((always_inline))
#	define LFORCEINLINE_LAMBDA __attribute__((always_inline))
#else
#	define LRESTRICT
#	define LFORCEINLINE inline
#	define LFORCEINLINE_LAMBDA
#endif
