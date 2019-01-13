#pragma once
#include<memory>

#include<Surface.h>

class Sphere : public Surface
{
public:
	Sphere(Vector3f c, float r)
		: center(c), r(r){}

	~Sphere();

	bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) override;

private:
	Vector3f center;
	float r;
};

