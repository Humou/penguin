#pragma once
#include<iostream>
#include<cmath>
#include<assert.h>

class Vector3f {
public:
	Vector3f(float x = 0, float y = 0, float z = 0)
		:x(x), y(y), z(z) {
		//assert(!hasNaNs());
	}
	Vector3f(float v)
		:x(v), y(v), z(v) {
		//assert(!hasNaNs());
	}
	~Vector3f() {}

	Vector3f operator+(const Vector3f &rhs) const {
		//assert(!rhs.hasNaNs());
		return Vector3f(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	void operator+=(const Vector3f &rhs) {
		//assert(!rhs.hasNaNs());
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}

	Vector3f operator-(const Vector3f &rhs) const {
		//assert(!rhs.hasNaNs());
		return Vector3f(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	void operator-=(const Vector3f &rhs) {
		//assert(!rhs.hasNaNs());
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
	}

	Vector3f operator*(const Vector3f &rhs) const {
		//assert(!rhs.hasNaNs());
		return Vector3f(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	void operator*=(const Vector3f &rhs) {
		//assert(!rhs.hasNaNs());
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
	}

	Vector3f operator/(const Vector3f &rhs) const {
		//assert(!rhs.hasNaNs());
		return Vector3f(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	void operator/=(const Vector3f &rhs) {
		//assert(!rhs.hasNaNs());
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;

	}

	/*void operator-() {
		x = -x;
		y = -y;
		z = -z;
	}*/
	bool hasNaNs()const { return std::isnan(x) | std::isnan(y) | std::isnan(z); }
	float lengthSquared() const;
	float length() const;
	
	//static fuction
	void normalize();

	static float dot(const Vector3f &a, const Vector3f &b);
	static Vector3f cross(const Vector3f &a, const Vector3f &b);
	static Vector3f normalized(const Vector3f &v);

	float x, y, z;
};
Vector3f operator-(float v, const Vector3f &rhs);
Vector3f operator*(const Vector3f &lhs, float v);
Vector3f operator*(float v, const Vector3f &rhs);

Vector3f operator/(const Vector3f &lhs, float v);
Vector3f operator/(float v, Vector3f &rhs);

bool operator == (const Vector3f &a, const Vector3f &b);
std::ostream& operator<<(std::ostream &out, const Vector3f &a);
