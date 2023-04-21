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

	LFORCEINLINE mat3 operator+(const mat3& mat) const
	{
		mat3 r;

		for (size_t i = 0; i != 3; i++)
			for (size_t j = 0; j != 3; j++)
				r[i][j] = m[i][j] + mat[i][j];

		return r;
	}
	LFORCEINLINE vec3 operator*(const vec3& v) const
	{
		const float x = m[0].x * v.x + m[1].x * v.y + m[2].x * v.z;
		const float y = m[0].y * v.x + m[1].y * v.y + m[2].y * v.z;
		const float z = m[0].z * v.x + m[1].z * v.y + m[2].z * v.z;
		return vec3(x, y, z);
	}
	LFORCEINLINE mat3 operator*(const mat3& m) const;

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

	void orthonormalize();
	mat3 getOrthonormalized() const;
};

mat3 mat3::operator*(const mat3& m) const
{
	mat3 result;

	const float* m1 = toFloatPtr();
	const float* m2 = m.toFloatPtr();
	float* r        = result.toFloatPtr();

	for (size_t i = 0; i != 3; ++i) {
		for (size_t j = 0; j != 3; ++j)
			*r++ = m1[0] * m2[0 * 3 + j] + m1[1] * m2[1 * 3 + j] + m1[2] * m2[2 * 3 + j];

		m1 += 3;
	}

	return result;
}

} // namespace ldr
