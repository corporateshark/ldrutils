/**
 * \file Matrix.cpp
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

#include "lmath/Matrix.h"

namespace ldr
{

void mat3::inverse()
{
	mat3 inv;

	inv[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
	inv[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
	inv[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];

	const float det = m[0][0] * inv[0][0] + m[0][1] * inv[1][0] + m[0][2] * inv[2][0];

	if (fabsf(det) < LMATH_EPSILON)
		return;

	const float invDet = 1.0f / det;

	inv[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
	inv[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
	inv[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
	inv[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];
	inv[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
	inv[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

	m[0][0] = inv[0][0] * invDet;
	m[0][1] = inv[0][1] * invDet;
	m[0][2] = inv[0][2] * invDet;

	m[1][0] = inv[1][0] * invDet;
	m[1][1] = inv[1][1] * invDet;
	m[1][2] = inv[1][2] * invDet;

	m[2][0] = inv[2][0] * invDet;
	m[2][1] = inv[2][1] * invDet;
	m[2][2] = inv[2][2] * invDet;
}

mat3 mat3::getInversed() const
{
	mat3 inv(*this);

	inv.inverse();

	return inv;
}

void mat3::transpose()
{
	for (size_t i = 0; i != 3; i++) {
		for (size_t j = 0; j != 3; j++) {
			const float tmp = m[i][j];
			m[i][j]         = m[j][i];
			m[j][i]         = tmp;
		}
	}
}

mat3 mat3::getTransposed() const
{
	mat3 t;

	for (size_t i = 0; i != 3; i++)
		for (size_t j = 0; j != 3; j++)
			t[i][j] = m[j][i];

	return t;
}

void mat3::orthonormalize()
{
	m[0].normalize();
	m[2] = m[0].cross(m[1]);
	m[2].normalize();
	m[1] = m[2].cross(m[0]);
	m[1].normalize();
}

mat3 mat3::getOrthonormalized() const
{
	mat3 n(*this);

	n.orthonormalize();

	return n;
}

// 'v' should be normalized
mat3 mat3::getRotateAngleAxis(float angleRad, const vec3& v)
{
	const float xx = v.x * v.x;
	const float xy = v.x * v.y;
	const float xz = v.x * v.z;

	const float yx = xy;
	const float yy = v.y * v.y;
	const float yz = v.y * v.z;

	const float zx = xz;
	const float zy = yz;
	const float zz = v.z * v.z;

	const float co = cosf(angleRad);
	const float si = sinf(angleRad);

	mat3 m;

	m[0][0] = xx + (1.0f - xx) * co;
	m[0][1] = xy * (1.0f - co) + v.z * si;
	m[0][2] = xz * (1.0f - co) - v.y * si;

	m[1][0] = yx * (1.0f - co) - v.z * si;
	m[1][1] = yy + (1.0f - yy) * co;
	m[1][2] = yz * (1.0f - co) + v.x * si;

	m[2][0] = zx * (1.0f - co) + v.y * si;
	m[2][1] = zy * (1.0f - co) - v.x * si;
	m[2][2] = zz + (1.0f - zz) * co;

	return m;
}

} // namespace ldr
