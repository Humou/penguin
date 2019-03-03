#pragma once
#include<memory>

#include<Ray.h>
#include<BRDF.h>
#include<ModifiedPhong.h>
#include<IntersectInfo.h>

class Surface
{
public:
	Surface(std::shared_ptr<BRDF> brdf = std::make_shared<ModifiedPhong>(), bool isLightSource = false, const Vector3f &color = Vector3f(1.0f, 1.0f, 1.0f), const Vector3f &e = Vector3f());
	virtual ~Surface();

	virtual bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) = 0;
	std::shared_ptr<BRDF> getBRDF() { return brdf; }
	bool isLight() { return isLightSource; }
	Vector3f getEmision() { return e; }

	int ID;
protected:
	std::shared_ptr<BRDF> brdf;
	bool isLightSource = false;
	Vector3f e;
	Vector3f color;

	static int curID;
};

