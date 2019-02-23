#pragma once
#include<memory>

#include<Surface.h>

class Sphere : public Surface
{
public:
	Sphere(Vector3f c, float r, std::shared_ptr<BRDF> brdf = std::make_shared<ModifiedPhong>(), bool isLightSource = false, const Vector3f &color = Vector3f(1.0f, 1.0f, 1.0f), const Vector3f &e = Vector3f())
		: Surface(brdf, isLightSource, color, e), center(c), r(r){}

	~Sphere();

	bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) override;

private:
	Vector3f center;
	float r;
};

