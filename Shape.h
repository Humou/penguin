#pragma once
#include"Ray.h"
#include"IntersectInfo.h"

class Shape
{
public:
	Shape();
	~Shape();

	virtual bool interect(const Ray &ray, IntersectInfo* info) = 0;
};

