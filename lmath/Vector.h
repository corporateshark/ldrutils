/**
 * \file Vector.h
 * \brief
 *
 * vec2/vec3/vec4
 *
 * \version 1.0.0
 * \date 03/04/2023
 * \author Sergey Kosarevsky, 2023
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 * https://github.com/corporateshark/lutils
 */

#pragma once

#include "lmath/Math.h"

namespace ldr
{

class vec2i;
class vec2;
class vec3;
class vec4;

inline vec2i operator*(int a, const vec2i& b);
inline vec2 operator*(float a, const vec2& b);
inline vec3 operator*(float a, const vec3& b);
inline vec4 operator*(float a, const vec4& b);

class vec2
{
 public:
	float x;
	float y;

 public:
	vec2(){}; // do not default-initialize
	vec2(float x, float y)
	: x(x)
	, y(y){};
	vec2(float x, int y)
	: x(x)
	, y(static_cast<float>(y)){};
	vec2(int x, float y)
	: x(static_cast<float>(x))
	, y(y){};
	vec2(int x, int y)
	: x(static_cast<float>(x))
	, y(static_cast<float>(y)){};
	vec2(unsigned int x, unsigned int y)
	: x(static_cast<float>(x))
	, y(static_cast<float>(y)){};
	explicit vec2(const float a)
	: x(a)
	, y(a){};

	LFORCEINLINE float operator[](size_t idx) const { return (&x)[idx]; };
	LFORCEINLINE float& operator[](size_t idx) { return (&x)[idx]; };
	LFORCEINLINE vec2 operator-() const { return vec2(-x, -y); }

	LFORCEINLINE vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }
	LFORCEINLINE vec2 operator+(const vec2& v) const { return vec2(x + v.x, y + v.y); }
	LFORCEINLINE vec2 operator*(const vec2& v) const { return vec2(x * v.x, y * v.y); }
	LFORCEINLINE vec2 operator/(const vec2& v) const { return vec2(x / v.x, y / v.y); }

	LFORCEINLINE vec2 operator*(float a) const { return vec2(x * a, y * a); }
	LFORCEINLINE vec2 operator/(float a) const { return vec2(x / a, y / a); }

	LFORCEINLINE vec2& operator+=(const vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	LFORCEINLINE vec2& operator-=(const vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	LFORCEINLINE vec2& operator/=(float a)
	{
		x /= a;
		y /= a;
		return *this;
	}

	LFORCEINLINE vec2& operator/=(const vec2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	LFORCEINLINE vec2& operator*=(float a)
	{
		x *= a;
		y *= a;
		return *this;
	}

	LFORCEINLINE vec2& operator*=(const vec2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	LFORCEINLINE bool operator==(const vec2& v) const { return (v.x == x) && (v.y == y); }
	LFORCEINLINE bool operator!=(const vec2& v) const { return (v.x != x) || (v.y != y); }

	LFORCEINLINE const float* toFloatPtr() const { return &x; };
	LFORCEINLINE float* toFloatPtr() { return &x; };

	LFORCEINLINE float length() const { return sqrtf(x * x + y * y); };
	LFORCEINLINE float sqrLength() const { return x * x + y * y; };
	LFORCEINLINE void normalize() { *this /= length(); }

	LFORCEINLINE vec2 getNormalized() const
	{
		vec2 v(*this);
		v.normalize();
		return v;
	};

	LFORCEINLINE float dot(const vec2& v) const { return x * v.x + y * v.y; }

	/// swizzles
	LFORCEINLINE vec2 yx() const { return vec2(y, x); };
};

class vec2i
{
 public:
	int x;
	int y;

 public:
	vec2i(){}; // do not default-initialize
	vec2i(int x, int y)
	: x(x)
	, y(y){};
	explicit vec2i(int a)
	: x(a)
	, y(a){};
	explicit vec2i(const vec2& v)
	: x(static_cast<int>(v.x))
	, y(static_cast<int>(v.y)){};

	LFORCEINLINE int operator[](size_t idx) const { return (&x)[idx]; };
	LFORCEINLINE int& operator[](size_t idx) { return (&x)[idx]; };

	LFORCEINLINE vec2i operator-(const vec2i& v) const { return vec2i(x - v.x, y - v.y); }
	LFORCEINLINE vec2i operator+(const vec2i& v) const { return vec2i(x + v.x, y + v.y); }

	LFORCEINLINE bool operator==(const vec2i& v) const { return (v.x == x) && (v.y == y); }
	LFORCEINLINE bool operator!=(const vec2i& v) const { return (v.x != x) || (v.y != y); }

	LFORCEINLINE vec2i operator*(int a) const { return vec2i(x * a, y * a); }
	LFORCEINLINE vec2i operator/(int a) const { return vec2i(x / a, y / a); }

	LFORCEINLINE const int* toIntPtr() const { return &x; };
	LFORCEINLINE int* toIntPtr() { return &x; };

	LFORCEINLINE float length() const { return sqrtf(static_cast<float>(x * x + y * y)); };
	LFORCEINLINE int sqrLength() const { return x * x + y * y; };
};

class vec3
{
 public:
	float x;
	float y;
	float z;

 public:
	vec3(){}; // do not default-initialize
	vec3(float x, float y)
	: x(x)
	, y(y)
	, z(0){};
	vec3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z){};
	vec3(int x, int y, int z)
	: x(static_cast<float>(x))
	, y(static_cast<float>(y))
	, z(static_cast<float>(z)){};
	vec3(const vec2& v, float z)
	: x(v.x)
	, y(v.y)
	, z(z){};
	explicit vec3(const float* f3)
	: x(f3[0])
	, y(f3[1])
	, z(f3[2]){};
	explicit vec3(const vec2& v)
	: x(v.x)
	, y(v.y)
	, z(0){};
	explicit vec3(int a)
	: x(static_cast<float>(a))
	, y(static_cast<float>(a))
	, z(static_cast<float>(a)){};
	explicit vec3(float a)
	: x(a)
	, y(a)
	, z(a){};

	LFORCEINLINE float operator[](size_t idx) const { return (&x)[idx]; }
	LFORCEINLINE float& operator[](size_t idx) { return (&x)[idx]; }

	LFORCEINLINE vec3 operator-() const { return vec3(-x, -y, -z); }
	LFORCEINLINE vec3 operator+() const { return vec3(+x, +y, +z); }

	LFORCEINLINE vec3 operator*(const float a) const { return vec3(x * a, y * a, z * a); }
	LFORCEINLINE vec3 operator/(const float a) const { return vec3(x / a, y / a, z / a); }

	LFORCEINLINE vec3 operator/(const vec3& v) const { return vec3(x / v.x, y / v.y, z / v.z); }

	LFORCEINLINE vec3 operator-(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); }
	LFORCEINLINE vec3 operator+(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); }

	LFORCEINLINE vec3& operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	LFORCEINLINE vec3& operator/=(float a)
	{
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	LFORCEINLINE vec3& operator+=(const vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	LFORCEINLINE vec3& operator-=(const vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	LFORCEINLINE bool operator==(const vec3& v) const { return (v.x == x) && (v.y == y) && (v.z == z); }
	LFORCEINLINE bool operator!=(const vec3& v) const { return (v.x != x) || (v.y != y) || (v.z != z); }

	LFORCEINLINE vec3 operator*(const vec3& v) const { return vec3(x * v.x, y * v.y, z * v.z); }

	LFORCEINLINE const float* toFloatPtr() const { return &x; }
	LFORCEINLINE float* toFloatPtr() { return &x; }

	LFORCEINLINE vec2 toVector2() const { return vec2(x, y); }

	LFORCEINLINE float length() const { return sqrt(x * x + y * y + z * z); }
	LFORCEINLINE float sqrLength() const { return x * x + y * y + z * z; }
	LFORCEINLINE void normalize() { *this /= length(); }

	LFORCEINLINE vec3 getNormalized() const
	{
		vec3 v(*this);
		v.normalize();
		return v;
	};

	LFORCEINLINE float dot(const vec3& v) const { return x * v.x + y * v.y + z * v.z; }
	LFORCEINLINE vec3 cross(const vec3& v) const { return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

	/// swizzles
	LFORCEINLINE vec3 xzy() const { return vec3(x, z, y); }
	LFORCEINLINE vec3 yzx() const { return vec3(y, z, x); }
	LFORCEINLINE vec2 xz() const { return vec2(x, z); }
};

class vec3i
{
 public:
	int x;
	int y;
	int z;

 public:
	vec3i(){}; // do not default-initialize
	vec3i(int x, int y, int z)
	: x(x)
	, y(y)
	, z(z){};
	explicit vec3i(int a)
	: x(a)
	, y(a)
	, z(a){};

	LFORCEINLINE int operator[](size_t idx) const { return (&x)[idx]; }
	LFORCEINLINE int& operator[](size_t idx) { return (&x)[idx]; }

	LFORCEINLINE vec3i operator-(const vec3i& v) const { return vec3i(x - v.x, y - v.y, z - v.z); }
	LFORCEINLINE vec3i operator+(const vec3i& v) const { return vec3i(x + v.x, y + v.y, z + v.z); }

	LFORCEINLINE bool operator==(const vec3i& v) const { return (v.x == x) && (v.y == y) && (v.z == z); }
	LFORCEINLINE bool operator!=(const vec3i& v) const { return (v.x != x) || (v.y != y) || (v.z != z); }

	LFORCEINLINE vec3i operator*(int a) const { return vec3i(x * a, y * a, z * a); }
	LFORCEINLINE vec3i operator/(int a) const { return vec3i(x / a, y / a, z / a); }

	LFORCEINLINE const int* toIntPtr() const { return &x; }
	LFORCEINLINE int* toIntPtr() { return &x; }

	LFORCEINLINE float length() const { return toVector3().length(); }
	LFORCEINLINE int sqrLength() const { return x * x + y * y + z * z; }

	LFORCEINLINE vec3 toVector3() const { return vec3(x, y, z); }
};

class vec4i
{
 public:
	int x;
	int y;
	int z;
	int w;

 public:
	vec4i(){}; // do not default-initialize
	vec4i(int x, int y, int z, int w)
	: x(x)
	, y(y)
	, z(z)
	, w(w){};
	vec4i(float x, float y, float z, float w)
	: x(static_cast<int>(x))
	, y(static_cast<int>(y))
	, z(static_cast<int>(z))
	, w(static_cast<int>(w)){};
	explicit vec4i(int a)
	: x(a)
	, y(a)
	, z(a)
	, w(a){};

	LFORCEINLINE int operator[](size_t idx) const { return (&x)[idx]; }
	LFORCEINLINE int& operator[](size_t idx) { return (&x)[idx]; }

	LFORCEINLINE vec4i operator-(const vec4i& v) const { return vec4i(x - v.x, y - v.y, z - v.z, w - v.w); }
	LFORCEINLINE vec4i operator+(const vec4i& v) const { return vec4i(x + v.x, y + v.y, z + v.z, w + v.w); }

	LFORCEINLINE vec4i& operator-=(const vec4i& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	LFORCEINLINE vec4i& operator+=(const vec4i& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	LFORCEINLINE bool operator==(const vec4i& v) const { return (v.x == x) && (v.y == y) && (v.z == z) && (v.w == w); }
	LFORCEINLINE bool operator!=(const vec4i& v) const { return (v.x != x) || (v.y != y) || (v.z != z) || (v.w != w); }

	LFORCEINLINE int dot(const vec4i& v) const { return (x * v.x + y * v.y + z * v.z + w * v.w); }

	/// swizzles
	LFORCEINLINE vec2i xy() const { return vec2i(x, y); }
	LFORCEINLINE vec2i yx() const { return vec2i(y, x); }
	LFORCEINLINE vec3i xyz() const { return vec3i(x, y, z); }
	LFORCEINLINE vec3i zyx() const { return vec3i(z, y, x); }
};

class vec4
{
 public:
	float x;
	float y;
	float z;
	float w;

 public:
	vec4(){}; // do not default-initialize
	vec4(float x, float y)
	: x(x)
	, y(y)
	, z(0)
	, w(0){};
	vec4(float x, float y, float z, float w)
	: x(x)
	, y(y)
	, z(z)
	, w(w){};
	vec4(int x, int y, int z, int w)
	: x(static_cast<float>(x))
	, y(static_cast<float>(y))
	, z(static_cast<float>(z))
	, w(static_cast<float>(w)){};
	vec4(const vec2& v, float z, float w)
	: x(v.x)
	, y(v.y)
	, z(z)
	, w(w){};
	vec4(const vec3& v, float w)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(w){};
	explicit vec4(const float* f4)
	: x(f4[0])
	, y(f4[1])
	, z(f4[2])
	, w(f4[3]){};
	explicit vec4(int a)
	: x(static_cast<float>(a))
	, y(static_cast<float>(a))
	, z(static_cast<float>(a))
	, w(static_cast<float>(a)){};
	explicit vec4(float a)
	: x(a)
	, y(a)
	, z(a)
	, w(a){};
	explicit vec4(const vec2& v)
	: x(v.x)
	, y(v.y)
	, z(0)
	, w(0){};
	explicit vec4(const vec3& v)
	: x(v.x)
	, y(v.y)
	, z(v.z)
	, w(0){};
	explicit vec4(const vec4i& v)
	: x(static_cast<float>(v.x))
	, y(static_cast<float>(v.y))
	, z(static_cast<float>(v.z))
	, w(static_cast<float>(v.w)){};

	LFORCEINLINE float operator[](size_t idx) const { return (&x)[idx]; }
	LFORCEINLINE float& operator[](size_t idx) { return (&x)[idx]; }

	LFORCEINLINE vec4 operator-(const vec4& v) const { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
	LFORCEINLINE vec4 operator+(const vec4& v) const { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }

	LFORCEINLINE vec4 operator*(float a) const { return vec4(x * a, y * a, z * a, w * a); }
	LFORCEINLINE vec4 operator/(float a) const { return vec4(x / a, y / a, z / a, w / a); }

	LFORCEINLINE vec4& operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;
		return *this;
	}

	LFORCEINLINE vec4& operator/=(float a)
	{
		x /= a;
		y /= a;
		z /= a;
		w /= a;
		return *this;
	}

	LFORCEINLINE vec4& operator-=(const vec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	LFORCEINLINE vec4& operator+=(const vec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	LFORCEINLINE bool operator==(const vec4& v) const { return (v.x == x) && (v.y == y) && (v.z == z) && (v.w == w); }
	LFORCEINLINE bool operator!=(const vec4& v) const { return (v.x != x) || (v.y != y) || (v.z != z) || (v.w != w); }

	LFORCEINLINE vec4 operator*(const vec4& v) const { return vec4(x * v.x, y * v.y, z * v.z, w * v.w); }

	LFORCEINLINE float dot(const vec4& v) const { return (x * v.x + y * v.y + z * v.z + w * v.w); }

	LFORCEINLINE const float* toFloatPtr() const { return &x; }
	LFORCEINLINE float* toFloatPtr() { return &x; }

	LFORCEINLINE vec2 toVector2() const { return vec2(x, y); }
	LFORCEINLINE vec3 toVector3() const { return vec3(x, y, z); }

	LFORCEINLINE float length() const { return sqrt(x * x + y * y + z * z + w * w); }
	LFORCEINLINE float sqrLength() const { return x * x + y * y + z * z + w * w; }
	LFORCEINLINE void normalize() { *this /= length(); }

	LFORCEINLINE vec4 getNormalized() const
	{
		vec4 v(*this);
		v.normalize();
		return v;
	};

	/// swizzles
	LFORCEINLINE vec4 bgra() const { return vec4(z, y, x, w); };
	LFORCEINLINE vec2 xy() const { return vec2(x, y); }
	LFORCEINLINE vec2 yx() const { return vec2(y, x); }
	LFORCEINLINE vec2 zw() const { return vec2(z, w); }
	LFORCEINLINE vec3 xyz() const { return vec3(x, y, z); }
	LFORCEINLINE vec3 xzy() const { return vec3(x, z, y); }
	LFORCEINLINE vec3 yxz() const { return vec3(y, x, z); }
	LFORCEINLINE vec3 yzx() const { return vec3(y, z, x); }
	LFORCEINLINE vec3 zyx() const { return vec3(z, y, x); }
	LFORCEINLINE vec3 zyz() const { return vec3(z, y, z); }
};

LFORCEINLINE vec2 operator*(float a, const vec2& b)
{
	return vec2(b.x * a, b.y * a);
}

LFORCEINLINE vec2i operator*(int a, const vec2i& b)
{
	return vec2i(b.x * a, b.y * a);
}

LFORCEINLINE vec3 operator*(float a, const vec3& b)
{
	return vec3(b.x * a, b.y * a, b.z * a);
}

LFORCEINLINE vec4 operator*(float a, const vec4& b)
{
	return vec4(b.x * a, b.y * a, b.z * a, b.w * a);
}

LFORCEINLINE vec2 normalize(const vec2 v)
{
	return v / v.length();
}

LFORCEINLINE vec3 normalize(const vec3& v)
{
	return v / v.length();
}

LFORCEINLINE vec4 normalize(const vec4& v)
{
	return v / v.length();
}

LFORCEINLINE vec3 cross(const vec3& a, const vec3& b)
{
	return a.cross(b);
}

// 32-bit RGBA colors, etc
class vec4b
{
 public:
	uint8_t x;
	uint8_t y;
	uint8_t z;
	uint8_t w;

 public:
	vec4b(){}; // do not default-initialize
	vec4b(uint8_t x, uint8_t y, uint8_t z, uint8_t w)
	: x(x)
	, y(y)
	, z(z)
	, w(w){};
	explicit vec4b(const uint8_t a)
	: x(a)
	, y(a)
	, z(a)
	, w(a){};
	explicit vec4b(const vec4& v)
	: x(static_cast<uint8_t>(v.x * 255.0f))
	, y(static_cast<uint8_t>(v.y * 255.0f))
	, z(static_cast<uint8_t>(v.z * 255.0f))
	, w(static_cast<uint8_t>(v.w * 255.0f)){};
};

} // namespace ldr
