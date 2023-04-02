/**
 * \file Math.h
 * \brief
 *
 * Math utilities
 *
 * \version 1.0.0
 * \date 02/04/2023
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#pragma once

#include <stdint.h>

#include "lutils/Macros.h"

#define LMATH_INFINITY 1e30f
#define LMATH_EPSILON  1e-8f
#define LMATH_PI       3.14159265358979323846f
#define LMATH_TWOPI    6.28318530717958647692f
#define LMATH_HALFPI   1.57079632679489661923f
#define LMATH_SQRT2    1.41421356237309504880f
// Pi/180
#define LMATH_DTOR  0.01745329251994329577f
// 180/Pi
#define LMATH_RTOD 57.29577951308232087679f
// ln(0.5)^-1
#define LMATH_LOGHALFINV -1.44269504088896340736f

namespace ldr
{

LFORCEINLINE float absf(float v)
{
	return (v > 0.0f) ? v : -v;
}

LFORCEINLINE float minf(float a, float b)
{
	return (a < b) ? a : b;
}

LFORCEINLINE float maxf(float a, float b)
{
	return (a > b) ? a : b;
}

LFORCEINLINE float degToRad(float deg)
{
	return deg * LMATH_DTOR;
}

LFORCEINLINE float radToDeg(float rad)
{
	return rad * LMATH_RTOD;
}

LFORCEINLINE void swapf(float& v1, float& v2)
{
	const float tmp = v1;

	v1 = v2;
	v2 = tmp;
}

// note: returns `true` for 0
LFORCEINLINE bool isPowerOf2(uint32_t n)
{
	return (n & (n - 1)) == 0;
}

// note: returns `true` for 0
LFORCEINLINE bool isPowerOf2(uint64_t n)
{
	return (n & (n - 1)) == 0;
}

// note: return 0 on overflow
LFORCEINLINE uint32_t getNextPowerOf2(uint32_t n)
{
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	return n + 1;
}

// note: return 0 on overflow
LFORCEINLINE uint64_t getNextPowerOf2(uint64_t n)
{
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	n |= (n >> 32);
	return n + 1;
}

} // namespace ldr
