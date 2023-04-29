/**
 * \file lmathTests.cpp
 * \brief
 *
 * lmath tests
 *
 * \version 1.0.0
 * \date 15/03/2023
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/ldrutils
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include <lmath/Blending.h>
#include <lmath/Geometry.h>
#include <lmath/Math.h>
#include <lmath/Matrix.h>
#include <lmath/Plane.h>
#include <lmath/Vector.h>

namespace ltests
{

GTEST_TEST(lmath, lmath_status)
{
#if defined(LMATH_USE_SSE4)
	printf("SSE4: on\n");
#else
	printf("SSE4: off\n");
#endif // LMATH_USE_SSE4

#if defined(LMATH_USE_AVX)
	printf("AVX : on\n");
#else
	printf("AVX : off\n");
#endif // LMATH_USE_AVX

#if defined(LMATH_USE_AVX2)
	printf("AVX2: on\n");
#else
	printf("AVX2: off\n");
#endif // LMATH_USE_AVX2

	ASSERT_TRUE(true);
}

GTEST_TEST(lmath, vec2_constructors)
{
	const float value = 32167.0f;
	vec2 v(value);

	ASSERT_TRUE(v.x == value);
	ASSERT_TRUE(v.y == value);

	v = vec2(1.0f, 2.0f);

	ASSERT_TRUE(v.x == 1.0f);
	ASSERT_TRUE(v.y == 2.0f);
}

GTEST_TEST(lmath, vec2_arithmetic)
{
	vec2 v = vec2(1.0f, 2.0f) + vec2(3.0f, 5.0f);

	ASSERT_TRUE(v.x == 4.0f);
	ASSERT_TRUE(v.y == 7.0f);

	v -= vec2(1.0f);

	ASSERT_TRUE(v.x == 3.0f);
	ASSERT_TRUE(v.y == 6.0f);

	v *= vec2(2.0f, 2.0f);

	ASSERT_TRUE(v.x == 6.0f);
	ASSERT_TRUE(v.y == 12.0f);

	v /= vec2(3.0f, 6.0f);

	ASSERT_TRUE(v.x == 2.0f);
	ASSERT_TRUE(v.y == 2.0f);

	const float f = dot(vec2(5.0f, 7.0f), vec2(3.0f, 9.0f));

	ASSERT_TRUE(f == (5.0f * 3.0f) + (7.0f * 9.0f));
}

GTEST_TEST(lmath, vec2_functions)
{
	ASSERT_TRUE(vec2(2.0f, 0.0f).length() == 2.0f);
	ASSERT_TRUE(vec2(0.0f, 2.0f).length() == 2.0f);
	ASSERT_TRUE(vec2(1.0f, 1.0f).sqrLength() == 2.0f);
	ASSERT_TRUE(vec2(3.0f, 5.0f).sum() == 8.0f);
	ASSERT_TRUE(vec2(3.0f, 5.0f).avg() == 4.0f);
	ASSERT_TRUE(vec2(3.0f, 5.0f).stdDev() == 1.0f);
	ASSERT_TRUE(vec2(2.0f, 0.0f).getNormalized().x == 1.0f);
	ASSERT_TRUE(vec2(0.0f, 2.0f).getNormalized().y == 1.0f);

	vec2 v1(3.0f, 5.0f);
	vec2 v2(2.0f, 6.0f);

	vec2 vmin = v1.getMinVector(v2);
	ASSERT_TRUE(vmin.x == 2.0f && vmin.y == 5.0f);

	vec2 vmax = v1.getMaxVector(v2);
	ASSERT_TRUE(vmax.x == 3.0f && vmax.y == 6.0f);

	v1 = vec2(10, -5);
	v2 = v1.getOrthogonalVector();
	ASSERT_TRUE(dot(v1, v2) == 0.0f);

	v2 = vec2(1.0f, 2.0f) * vec2(0.0f);
	ASSERT_TRUE(v2.isZeroVector(LMATH_EPSILON));

	v2 = vec2(-128, +128).saturate();
	ASSERT_TRUE(v2.x == 0.0f && v2.y == 1.0f);

	ASSERT_TRUE(vec2(-3.0f, 1.0f).abs().x == 3.0f);
	ASSERT_TRUE(vec2(1.0f, -3.0f).abs().y == 3.0f);

	v1 = vec2(1.0f, 2.0f);
	v2 = v1.yx();
	ASSERT_TRUE(v2.x == 2.0f && v2.y == 1.0f);
	ASSERT_TRUE(v1 == v2.yx());
}

GTEST_TEST(lmath, mat3_zero_identity)
{
	mat3 m = mat3::getIdentity();

	ASSERT_TRUE(m[0][0] == 1.0f);
	ASSERT_TRUE(m[1][1] == 1.0f);
	ASSERT_TRUE(m[2][2] == 1.0f);

	m.makeZero();

	ASSERT_TRUE(m[0][0] == 0.0f);
	ASSERT_TRUE(m[1][1] == 0.0f);
	ASSERT_TRUE(m[2][2] == 0.0f);
}

GTEST_TEST(lmath, mat4_zero_identity)
{
	mat4 m = mat4::getIdentity();

	ASSERT_TRUE(m[0][0] == 1.0f);
	ASSERT_TRUE(m[1][1] == 1.0f);
	ASSERT_TRUE(m[2][2] == 1.0f);
	ASSERT_TRUE(m[3][3] == 1.0f);

	m.makeZero();

	ASSERT_TRUE(m[0][0] == 0.0f);
	ASSERT_TRUE(m[1][1] == 0.0f);
	ASSERT_TRUE(m[2][2] == 0.0f);
	ASSERT_TRUE(m[3][3] == 0.0f);
}

namespace {

void printMat(const mat3& m)
{
	for (size_t i = 0; i != 3; ++i) {
		for (size_t j = 0; j != 3; ++j) {
			printf("%8.4f", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

mat3 getRotateRef(const vec3& v1, const vec3& v2)
{
	vec3 axis = cross(v1, v2);

	if (axis.length() <= LMATH_EPSILON) {
		axis = vec3(0.0f, 0.0f, 1.0f);
	}

	const float cosAngle = dot(v1, v2);

	return mat3::getRotateAngleAxis(acosf(ldr::clamp(cosAngle, -1.0f, 1.0f)), normalize(axis));
}

void testRotate(const vec3& v1, const vec3& v2, float eps)
{
	mat3 m1 = mat3::getRotate(v1, v2);
	mat3 m2 = getRotateRef(v1, v2);

	if (!m1.isEqual(m2, eps)) {
		printMat(m1);
		printMat(m2);
	}

	ASSERT_TRUE(m1.isEqual(m2, eps));
}

} // namespace

GTEST_TEST(lmath, mat3_rotate1)
{
	const float eps = 0.0000001f;
	testRotate(vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), eps);
	testRotate(vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), eps);
	testRotate(vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), eps);

	testRotate(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), eps);
	testRotate(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), eps);
	testRotate(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), eps);

	testRotate(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), eps);
	testRotate(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), eps);
	testRotate(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), eps);
}

GTEST_TEST(lmath, mat3_rotate2)
{
	const float eps = 0.000001f;
	testRotate(normalize(vec3(1.0f, 1.0f, 1.0f)), normalize(-vec3(1.0f, 1.0f, 0.0f)), eps);
	testRotate(normalize(vec3(1.0f, 1.0f, 0.0f)), normalize(-vec3(0.0f, 1.0f, 1.0f)), eps);
	testRotate(normalize(vec3(0.0f, 1.0f, 1.0f)), normalize(-vec3(1.0f, 0.0f, 1.0f)), eps);
	testRotate(normalize(vec3(1.0f, 0.0f, 1.0f)), normalize(-vec3(1.0f, 1.0f, 1.0f)), eps);
}

} // namespace ltests
