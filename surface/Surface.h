#pragma once
#include<memory>

#include<Ray.h>
#include<BRDF.h>
#include<Material.h>
#include<ModifiedPhong.h>
#include<IntersectInfo.h>

class Surface
{
public:
	Surface(Material material);
	virtual ~Surface();

	virtual bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) = 0;
	bool isLight() { return material.isLight; }
	Vector3f getEmision() { return material.emission; }

	Material material;
};

