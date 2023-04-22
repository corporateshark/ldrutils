/**
 * \file Macros.h
 * \brief
 *
 * Useful macros - utils
 *
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#pragma once

// clang-format off

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

#if defined(__SSE4_1__) || defined(__AVX__) || defined(__AVX2__)
#	define LMATH_USE_SSE4 1
#endif // __SSE4_1__

#if defined(__AVX__) || defined(__AVX2__)
#	define LMATH_USE_AVX 1
#endif // __AVX__

#if defined(__AVX2__)
#	define LMATH_USE_AVX2 1
#endif // __AVX2__

// clang-format on
