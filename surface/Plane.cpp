#include "Plane.h"



Plane::Plane(const Vector3f &V00, const Vector3f &V10, const Vector3f &V11, const Vector3f &V01, Material material)
	:Surface(material), V00(V00), V10(V10), V11(V11), V01(V01)
{
}


Plane::~Plane()
{
}

bool Plane::interect(const Ray & ray, std::shared_ptr<IntersectInfo> info)
{
	float t;
	if (!interect(ray.o, ray.d, t)) return false;

	if (info->isValid && t >= info->t) return false;

	//当前交点为最近交点或第一个交点，则需要改变info
	info->p = ray.evaluate(t);
	info->t = t;
	info->isValid = true;
	info->normal = Vector3f::cross(V10 - V00, V01 - V00);
	;
	info->normal.normalize();
	info->color = material.color;
	if (isLight()) {
		info->isLightSource = true;
		info->e = getEmision();
	}
	info->wi = material.sampleDirection(info->normal, 0.0 - Vector3f::normalized(ray.d));
	
	return true;
}

bool Plane::interect(const Vector3f & O, const Vector3f & D, float &t)
{
	Vector3f E01 = V10 - V00;
	Vector3f E03 = V01 - V00;
	Vector3f P = Vector3f::cross(D, E03);
	float det = Vector3f::dot(E01, P);
	if (std::abs(det) < 10e-5) return false;
	Vector3f T = O - V00;
	float alpha = Vector3f::dot(T, P) / det;
	if (alpha < 0) return false;
	if (alpha > 1)return false;

	Vector3f Q = Vector3f::cross(T, E01);
	float belta = Vector3f::dot(D, Q) / det;
	if (belta < 0) return false;
	if (belta > 1) return false;

	if ((alpha + belta) > 1) {
		Vector3f E23 = V01 - V11;
		Vector3f E21 = V10 - V11;
		Vector3f P0 = Vector3f::cross(D, E21);
		float det0 = Vector3f::dot(E23, P0);

		if (std::abs(det0) < 10e-5) return false;
		Vector3f T0 = O - V11;
		float alpha0 = Vector3f::dot(T0, P0) / det0;

		if (alpha0 < 0) return false;
		Vector3f Q0 = Vector3f::cross(T0, E23);
		float belta0 = Vector3f::dot(D, Q0) / det0;
		if (belta0 < 0) return false;
	}

	t = Vector3f::dot(E03, Q) / det;
	if (t <= 0) return false;

	return true;
}
