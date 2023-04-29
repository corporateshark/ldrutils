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
	union {
		vec4 p;
		struct {
			vec3 n;
			float d;
		};
	};

 public:
	plane3()
	: p(0.0f, 0.0f, 1.0f, 0.0f){};
	/// from a plane equation
	explicit plane3(const vec4& v)
	: p(v){};
	/// from a normal and parameter
	explicit plane3(const vec3& normal, float d)
	: p(normal, d){};
	/// from a plane equation
	plane3(float nx, float ny, float nz, float d)
	: p(vec3(nx, ny, nz), d){};
	/// from a point and normal
	plane3(const vec3& pt, const vec3& normal)
	: p(normal, -dot(pt, normal)){};
	/// from 3 points
	plane3(const vec3& p1, const vec3& p2, const vec3& p3)
	: plane3(p1, normalize(cross(p2 - p1, p3 - p1))){};
	LFORCEINLINE float operator[](size_t idx) const { return p[idx]; };
	LFORCEINLINE float& operator[](size_t idx) { return p[idx]; };
	LFORCEINLINE const float* toFloatPtr() const { return p.toFloatPtr(); }
	LFORCEINLINE float* toFloatPtr() { return p.toFloatPtr(); }
	LFORCEINLINE vec3 toVector3() const { return n; }
	LFORCEINLINE vec3 getNormal() const { return n; }

	LFORCEINLINE void invert() { n = -n; }
	LFORCEINLINE plane3 getInverted() const { return plane3(-n, d); }

	LFORCEINLINE float getDistanceToPointSigned(const vec3& pt) const { return n.dot(pt) + d; }
	LFORCEINLINE float getDistanceToPoint(const vec3& pt) const { return ldr::absf(getDistanceToPointSigned(pt)); }

	/// intersection of N-ray with this plane
	LFORCEINLINE vec3 getPointOnPlane() const { return d * n / n.dot(n); }
	/// project vector's ends to plane's normal
	LFORCEINLINE vec3 projectToNormal(const vec3& v) const { return (v * n) * n; }
	/// project vector's ends to plane
	LFORCEINLINE vec3 projectPoint(const vec3& pt) const { return pt - projectToNormal(pt) + d * n; }

	LFORCEINLINE void buildBasis(vec3* v1, vec3* v2) const
	{
		*v1 = n.getOrthogonalVector();
		*v2 = normalize(cross(n, *v1));
	}
};

static_assert(sizeof(plane3) == sizeof(vec4));

} // namespace ldr

#if defined(LMATH_USE_SHORTCUT_TYPES)
using plane3 = ldr::plane3;
#endif // LMATH_USE_SHORTCUT_TYPES
