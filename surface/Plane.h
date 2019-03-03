#pragma once
#include<Surface.h>

class Plane : public Surface 
{
public:
	Plane(const Vector3f &V00, const Vector3f &V10, const Vector3f &V11, const Vector3f &V01, bool isLight = true, const Vector3f &color = Vector3f(0.5, 0.5, 0.5), const Vector3f &e = Vector3f(5, 5, 5));
	~Plane();

	bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) override;

	bool interect(const Vector3f &O, const Vector3f &D, float &t);
	Vector3f V00, V10, V11, V01;
};

