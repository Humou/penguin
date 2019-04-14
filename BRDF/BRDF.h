#pragma once
#include<Vector3f.h>
const double PI = 3.14159265;
class BRDF
{
public:
	BRDF();
	virtual ~BRDF();

	virtual Vector3f sample(float &f, float &pdf, Vector3f &normal, Vector3f &w0) = 0;
};

