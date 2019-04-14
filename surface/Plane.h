#pragma once
#include<Surface.h>

class Plane : public Surface 
{
public:
	Plane(const Vector3f &V00, const Vector3f &V10, const Vector3f &V11, const Vector3f &V01, Material material);
	~Plane();

	bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) override;

	bool interect(const Vector3f &O, const Vector3f &D, float &t);
	Vector3f V00, V10, V11, V01;
};

