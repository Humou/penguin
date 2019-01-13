#pragma once
#include<vector3f.h>

class Ray
{
public:
	Ray(Vector3f o, Vector3f d)
		:o(o), d(d){}

	~Ray(){}

	Vector3f evaluate(float t) const { return o + t * d; }
	Vector3f o, d;
};

