#pragma once
#include<memory>

#include<Ray.h>
#include<IntersectInfo.h>

class Surface
{
public:
	Surface();
	virtual ~Surface();

	virtual bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) = 0;
};

