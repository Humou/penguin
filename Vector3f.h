#pragma once
#include<iostream>
#include<cmath>
class Vector3f {
public:
	Vector3f(float x = 0, float y = 0, float z = 0)
		:x(x), y(y), z(z) {}
	Vector3f(float v)
		:x(v), y(v), z(v) {}
	~Vector3f() {}

	Vector3f operator+(const Vector3f &rhs) const {
		return Vector3f(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	void operator+=(const Vector3f &rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}

	Vector3f operator-(const Vector3f &rhs) const {
		return Vector3f(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	void operator-=(const Vector3f &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
	}

	Vector3f operator*(const Vector3f &rhs) const {
		return Vector3f(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	void operator*=(const Vector3f &rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
	}

	Vector3f operator/(const Vector3f &rhs) const {
		/*if (rhs.x == 0 || rhs.y == 0 || rhs.z == 0) {
		std::cout << "Vector3f operator/(const Vector3f &rhs): divided by zero"<<std::endl;
		return Vector3f();
		}*/
		return Vector3f(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	void operator/=(const Vector3f &rhs) {
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;

	}
	float x, y, z;
};

Vector3f operator*(const Vector3f &lhs, float v);
Vector3f operator*(float v, const Vector3f &rhs);

Vector3f operator/(const Vector3f &lhs, float v);
Vector3f operator/(float v, Vector3f &rhs);

float lengthSquared(const Vector3f &a);
float length(const Vector3f &a);

float dot(const Vector3f &a, const Vector3f &b);
Vector3f cross(const Vector3f &a, const Vector3f &b);

std::ostream& operator<<(std::ostream &out, const Vector3f &a);