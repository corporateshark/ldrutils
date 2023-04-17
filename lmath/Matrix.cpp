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


} // namespace ldr
