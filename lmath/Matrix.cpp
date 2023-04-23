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

// https://iquilezles.org/articles/noacos/
// `v1` and `v2` should be normalized
mat3 mat3::getRotate(const vec3& v1, const vec3& v2)
{
	const vec3 v  = cross(v1, v2);
	const float c = dot(v1, v2);
	const float k = 1.0f / (1.0f + c);

	mat3 m;

	m[0][0] = v.x * v.x * k + c;
	m[0][1] = v.x * v.y * k + v.z;
	m[0][2] = v.x * v.z * k - v.y;

	m[1][0] = v.y * v.x * k - v.z;
	m[1][1] = v.y * v.y * k + c;
	m[1][2] = v.y * v.z * k + v.x;

	m[2][0] = v.z * v.x * k + v.y;
	m[2][1] = v.z * v.y * k - v.x;
	m[2][2] = v.z * v.z * k + c;

	return m;
}

void mat4::inverse()
{
	// 2x2 sub-determinants required to calculate the 4x4 determinant
	float d2_01_01 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	float d2_01_02 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
	float d2_01_03 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
	float d2_01_12 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
	float d2_01_13 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
	float d2_01_23 = m[0][2] * m[1][3] - m[0][3] * m[1][2];

	// 3x3 sub-determinants required to calculate the 4x4 determinant
	float d3_201_012 = m[2][0] * d2_01_12 - m[2][1] * d2_01_02 + m[2][2] * d2_01_01;
	float d3_201_013 = m[2][0] * d2_01_13 - m[2][1] * d2_01_03 + m[2][3] * d2_01_01;
	float d3_201_023 = m[2][0] * d2_01_23 - m[2][2] * d2_01_03 + m[2][3] * d2_01_02;
	float d3_201_123 = m[2][1] * d2_01_23 - m[2][2] * d2_01_13 + m[2][3] * d2_01_12;

	const float det = -d3_201_123 * m[3][0] + d3_201_023 * m[3][1] - d3_201_013 * m[3][2] + d3_201_012 * m[3][3];

	if (fabsf(det) < LMATH_EPSILON) {
		return;
	}

	const float invDet = 1.0f / det;

	// remaining 2x2 sub-determinants
	float d2_03_01 = m[0][0] * m[3][1] - m[0][1] * m[3][0];
	float d2_03_02 = m[0][0] * m[3][2] - m[0][2] * m[3][0];
	float d2_03_03 = m[0][0] * m[3][3] - m[0][3] * m[3][0];
	float d2_03_12 = m[0][1] * m[3][2] - m[0][2] * m[3][1];
	float d2_03_13 = m[0][1] * m[3][3] - m[0][3] * m[3][1];
	float d2_03_23 = m[0][2] * m[3][3] - m[0][3] * m[3][2];

	float d2_13_01 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
	float d2_13_02 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
	float d2_13_03 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
	float d2_13_12 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
	float d2_13_13 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
	float d2_13_23 = m[1][2] * m[3][3] - m[1][3] * m[3][2];

	// remaining 3x3 sub-determinants
	float d3_203_012 = m[2][0] * d2_03_12 - m[2][1] * d2_03_02 + m[2][2] * d2_03_01;
	float d3_203_013 = m[2][0] * d2_03_13 - m[2][1] * d2_03_03 + m[2][3] * d2_03_01;
	float d3_203_023 = m[2][0] * d2_03_23 - m[2][2] * d2_03_03 + m[2][3] * d2_03_02;
	float d3_203_123 = m[2][1] * d2_03_23 - m[2][2] * d2_03_13 + m[2][3] * d2_03_12;

	float d3_213_012 = m[2][0] * d2_13_12 - m[2][1] * d2_13_02 + m[2][2] * d2_13_01;
	float d3_213_013 = m[2][0] * d2_13_13 - m[2][1] * d2_13_03 + m[2][3] * d2_13_01;
	float d3_213_023 = m[2][0] * d2_13_23 - m[2][2] * d2_13_03 + m[2][3] * d2_13_02;
	float d3_213_123 = m[2][1] * d2_13_23 - m[2][2] * d2_13_13 + m[2][3] * d2_13_12;

	float d3_301_012 = m[3][0] * d2_01_12 - m[3][1] * d2_01_02 + m[3][2] * d2_01_01;
	float d3_301_013 = m[3][0] * d2_01_13 - m[3][1] * d2_01_03 + m[3][3] * d2_01_01;
	float d3_301_023 = m[3][0] * d2_01_23 - m[3][2] * d2_01_03 + m[3][3] * d2_01_02;
	float d3_301_123 = m[3][1] * d2_01_23 - m[3][2] * d2_01_13 + m[3][3] * d2_01_12;

	m[0][0] = -d3_213_123 * invDet;
	m[1][0] = +d3_213_023 * invDet;
	m[2][0] = -d3_213_013 * invDet;
	m[3][0] = +d3_213_012 * invDet;

	m[0][1] = +d3_203_123 * invDet;
	m[1][1] = -d3_203_023 * invDet;
	m[2][1] = +d3_203_013 * invDet;
	m[3][1] = -d3_203_012 * invDet;

	m[0][2] = +d3_301_123 * invDet;
	m[1][2] = -d3_301_023 * invDet;
	m[2][2] = +d3_301_013 * invDet;
	m[3][2] = -d3_301_012 * invDet;

	m[0][3] = -d3_201_123 * invDet;
	m[1][3] = +d3_201_023 * invDet;
	m[2][3] = -d3_201_013 * invDet;
	m[3][3] = +d3_201_012 * invDet;
}

mat4 mat4::getInversed() const
{
	mat4 inv(*this);

	inv.inverse();

	return inv;
}

void mat4::transpose()
{
	for (size_t i = 0; i != 4; i++) {
		for (size_t j = 0; j != 4; j++) {
			const float tmp = m[i][j];
			m[i][j]         = m[j][i];
			m[j][i]         = tmp;
		}
	}
}

mat4 mat4::getTransposed() const
{
	mat4 t;

	for (size_t i = 0; i != 4; i++)
		for (size_t j = 0; j != 4; j++)
			t[i][j] = m[j][i];

	return t;
}

mat4 mat4::getRotateAngleAxis(float angleRad, const vec3& axisNormalized)
{
	const mat3 m = mat3::getRotateAngleAxis(angleRad, axisNormalized);
	return mat4(m);
}
mat4 mat4::getRotate(const vec3& v1, const vec3& v2)
{
	const mat3 m = mat3::getRotate(v1, v2);
	return mat4(m);
}

mat4 mat4::getTranslate(const vec3& v)
{
	mat4 m;
	m[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
	m[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	m[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	m[3] = vec4(v, 1.0f);
	return m;
}

mat4 mat4::getScale(const vec3& v)
{
	mat4 m;
	m[0] = vec4(v.x, 0.0f, 0.0f, 0.0f);
	m[1] = vec4(0.0f, v.y, 0.0f, 0.0f);
	m[2] = vec4(0.0f, 0.0f, v.z, 0.0f);
	m[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

} // namespace ldr
