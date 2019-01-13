#include"Vector3f.h"

Vector3f operator*(const Vector3f &lhs, float v) {
	return Vector3f(lhs.x * v, lhs.y * v, lhs.z * v);
}

Vector3f operator*(float v, const Vector3f &rhs) {
	return rhs * v;
}

Vector3f operator/(const Vector3f &lhs, float v) {
	return lhs * (1 / v);
}

Vector3f operator/(float v, Vector3f &rhs) {
	return rhs / v;
}

float Vector3f::lengthSquared() const{
	return x * x + y * y + z * z;
}
float Vector3f::length() const{
	return std::sqrt(lengthSquared());
}

Vector3f Vector3f::normalize(const Vector3f & a)
{
	return a/a.length();
}

float Vector3f::dot(const Vector3f &a, const Vector3f &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3f Vector3f::cross(const Vector3f &a, const Vector3f &b) {
	return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

std::ostream& operator<<(std::ostream &out, const Vector3f &a) {
	out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
	return out;
}