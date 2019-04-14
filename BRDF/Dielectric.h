#pragma once
#include<BRDF.h>
#include<random>
class Dielectric : public BRDF
{
public:
	Dielectric();
	~Dielectric();

	Vector3f sampleReflect(float &f, float &pdf, Vector3f &normal, Vector3f &w0);
	Vector3f sampleRetract(float &f, float &pdf, Vector3f &normal, Vector3f &w0);

	virtual Vector3f sample(float &f, float &pdf, Vector3f &normal, Vector3f &w0) override;

	float fresnel(Vector3f &w0, Vector3f &n);

	float R0 = 0.4;
	float P = 0.4;
	float nt = 1.55;

	std::default_random_engine e;
	std::uniform_real_distribution<float> u;
};

