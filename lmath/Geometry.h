/**
 * \file Geometry.h
 * \brief
 *
 * Basic geometry utils
 *
 * \version 1.0.0
 * \date 14/04/2023
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#pragma once

#include "lmath/Math.h"
#include "lmath/Vector.h"

namespace ldr
{

LFORCEINLINE vec2 convertPolarToCartesian(float radius, float angleRad)
{
	return radius * vec2(cosf(angleRad), sinf(angleRad));
}

// (radius, thetaRad, phiRad) -> (x, y, z)
LFORCEINLINE vec3 convertSphericalToCartesian(float radius, float thetaRad, float phiRad)
{
	const float sinPhi   = sinf(phiRad);
	const float cosPhi   = cosf(phiRad);
	const float sinTheta = sinf(thetaRad);
	const float cosTheta = cosf(thetaRad);

	return radius * vec3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
}

// (radius, thetaRad, phiRad) -> (x, y, z)
LFORCEINLINE vec3 convertSphericalToCartesian(const vec3& s)
{
	return convertSphericalToCartesian(s.x, s.y, s.z);
}

// (x, y, z) -> (radius, thetaRad, phiRad)
LFORCEINLINE vec3 convertCartesianToSpherical(const vec3& p)
{
	const float r     = p.length();
	const float phi   = atan2(p.y / r, p.z / r);
	const float theta = atan2(p.toVector2().length(), p.z);

	return vec3(r, theta, phi);
}

inline vec3 getBarycentricCoordinates(const vec2i* pts, vec2i p)
{
	const vec3 v1(pts[2][0] - pts[0][0], pts[1][0] - pts[0][0], pts[0][0] - p.x);
	const vec3 v2(pts[2][1] - pts[0][1], pts[1][1] - pts[0][1], pts[0][1] - p.y);

	const vec3 u = cross(v1, v2);

	// the triangle is degenerate
	if (std::abs(u[2]) < 1)
		return vec3(-1, 1, 1);

	return vec3(1.0f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

inline vec3 getBarycentricCoordinates(const vec3* pts, vec3 p)
{
	const vec3 v2     = p - pts[0];
	const float d00   = dot(pts[1] - pts[0], pts[1] - pts[0]);
	const float d01   = dot(pts[1] - pts[0], pts[2] - pts[0]);
	const float d11   = dot(pts[2] - pts[0], pts[2] - pts[0]);
	const float d20   = dot(v2, pts[1] - pts[0]);
	const float d21   = dot(v2, pts[2] - pts[0]);
	const float scale = 1.0f / (d00 * d11 - d01 * d01);
	const float v     = (d11 * d20 - d01 * d21) * scale;
	const float w     = (d00 * d21 - d01 * d20) * scale;

	return vec3(1.0f - v - w, v, w);
}

LFORCEINLINE vec3 quantizeFloor(const vec3& v, float scale)
{
	return vec3(floor(v.x / scale) * scale, floor(v.y / scale) * scale, floor(v.z / scale) * scale);
}

LFORCEINLINE vec3 quantizeCeil(const vec3& v, float scale)
{
	return vec3(ceil(v.x / scale) * scale, ceil(v.y / scale) * scale, ceil(v.z / scale) * scale);
}

} // namespace ldr
