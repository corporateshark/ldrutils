/**
 * \file Plane.h
 * \brief
 *
 * 3d plane
 *
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#pragma once

#include <lmath/Vector.h>

namespace ldr
{

class plane3
{
 public:
	vec4 plane;

 public:
	plane3()
	: plane(0.0f, 0.0f, 1.0f, 0.0f){};

	/// from a plane equation
	explicit plane3(const vec4& v)
	: plane(v){};
	/// from a normal and parameter
	explicit plane3(const vec3& normal, float d)
	: plane(normal, d){};
	/// from a plane equation
	plane3(float nx, float ny, float nz, float d)
	: plane(vec3(nx, ny, nz), d){};
	/// from a point and normal
	plane3(const vec3& pt, const vec3& normal)
	: plane(normal, -dot(pt, normal)){};
	/// from 3 points
	plane3(const vec3& p1, const vec3& p2, const vec3& p3)
	: plane3(p1, normalize(cross(p2 - p1, p3 - p1))){};
	LFORCEINLINE float operator[](size_t idx) const { return plane[idx]; };
	LFORCEINLINE float& operator[](size_t idx) { return plane[idx]; };
	LFORCEINLINE const float* toFloatPtr() const { return plane.toFloatPtr(); }
	LFORCEINLINE float* toFloatPtr() { return plane.toFloatPtr(); }
	LFORCEINLINE vec3 toVector3() const { return plane.toVector3(); }
};

} // namespace ldr

#if defined(LMATH_USE_SHORTCUT_TYPES)
using plane3 = ldr::plane3;
#endif // LMATH_USE_SHORTCUT_TYPES
