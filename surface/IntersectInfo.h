#pragma once
#include<memory>

#include<Vector3f.h>
class Surface;
class IntersectInfo
{
public:
	IntersectInfo();
	~IntersectInfo();

	float t;
	bool isValid = false;
	Vector3f normal;
	std::shared_ptr<Surface> surface;
	Vector3f wi;
	float f, pdf;
	bool isLightSource = false;
	Vector3f e;
	Vector3f p;
};

