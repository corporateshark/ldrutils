/**
 * \file Matrix.h
 * \brief
 *
 * mat3
 *
 * \version 1.0.0
 * \date 16/04/2023
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#pragma once

#include "lmath/Vector.h"

namespace ldr
{

class mat3
{
 public:
	vec3 m[3];

 public:
	mat3(){}; // do not default-initialize
	LFORCEINLINE explicit mat3(float a)
	{
		m[0] = vec3(a);
		m[1] = vec3(a);
		m[2] = vec3(a);
	};
	LFORCEINLINE mat3(const vec3& x, const vec3& y, const vec3& z)
	{
		m[0] = x;
		m[1] = y;
		m[2] = z;
	};

	LFORCEINLINE vec3& operator[](size_t idx) { return m[idx]; };
	LFORCEINLINE const vec3& operator[](size_t idx) const { return m[idx]; };

	LFORCEINLINE const float* toFloatPtr() const { return m[0].toFloatPtr(); };
	LFORCEINLINE float* toFloatPtr() { return m[0].toFloatPtr(); };

	LFORCEINLINE void makeZero()
	{
		m[0] = vec3(0);
		m[1] = vec3(0);
		m[2] = vec3(0);
	};
	LFORCEINLINE void makeIdentity()
	{
		m[0] = vec3(1, 0, 0);
		m[1] = vec3(0, 1, 0);
		m[2] = vec3(0, 0, 1);
	};
	LFORCEINLINE static mat3 getIdentity() { return mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1)); };

	void inverse();
	mat3 getInversed() const;

	void transpose();
	mat3 getTransposed() const;
};

} // namespace ldr
