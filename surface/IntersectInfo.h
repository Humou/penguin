#pragma once
#include<Vector3f.h>

class IntersectInfo
{
public:
	IntersectInfo();
	~IntersectInfo();

	float t;
	bool isValid = false;
	Vector3f normal;
};

