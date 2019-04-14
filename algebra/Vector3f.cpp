#include"Vector3f.h"

Vector3f operator-(float v, const Vector3f & rhs)
{
	//assert(!rhs.hasNaNs());
	return Vector3f(v - rhs.x, v - rhs.y, v - rhs.z);
}

Vector3f operator*(const Vector3f &lhs, float v) {
	//assert(!lhs.hasNaNs());
	return Vector3f(lhs.x * v, lhs.y * v, lhs.z * v);
}

Vector3f operator*(float v, const Vector3f &rhs) {
	//assert(!rhs.hasNaNs());
	return rhs * v;
}

Vector3f operator/(const Vector3f &lhs, float v) {
	//assert(!lhs.hasNaNs());
	return lhs * (1 / v);
}

Vector3f operator/(float v, Vector3f &rhs) {
	//assert(!rhs.hasNaNs());
	return rhs / v;
}

float & Vector3f::operator[](unsigned int index)
{
	if (index == 0) return x;
	else if (index == 1) return y;
	else if (index == 2) return z;
}

float Vector3f::lengthSquared() const{
	return x * x + y * y + z * z;
}
float Vector3f::length() const{
	return std::sqrt(lengthSquared());
}

void Vector3f::normalize()
{
	float len = length();
	//*this = *this / length();
	x /= len; y /= len; z /= len;
}

float Vector3f::dot(const Vector3f &a, const Vector3f &b) {
	//assert(!a.hasNaNs());
	//assert(!b.hasNaNs());
	float ret = (a.x * b.x + a.y * b.y + a.z * b.z);
	if (std::isnan(ret)) {
		//std::cout << a << "  " << b << std::endl;
	}
	return ret;
}

Vector3f Vector3f::cross(const Vector3f &a, const Vector3f &b) {
	//assert(!a.hasNaNs());
	//assert(!b.hasNaNs());
	return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vector3f Vector3f::normalized(const Vector3f & v)
{
	if (v.length() == 0) return Vector3f();
	return v/v.length();
}

bool operator == (const Vector3f &a, const Vector3f &b) {
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}
std::ostream& operator<<(std::ostream &out, const Vector3f &a) {
	out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
	return out;
}

