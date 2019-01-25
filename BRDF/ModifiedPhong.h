#pragma once
#include<BRDF.h>
#include<random>

class ModifiedPhong : public BRDF
{
public:
	ModifiedPhong();
	~ModifiedPhong();

	Vector3f sample(float &f, float &pdf, const Vector3f &normal, const Vector3f &w0) override;
	Vector3f sampleDiffuse(float &f, float &pdf, const Vector3f &normal, const Vector3f &w0);
	Vector3f sampleSpecular(float &f, float &pdf, const Vector3f &normal, const Vector3f &w0);

private:
	float p_s, p_d, k_s;
	std::default_random_engine e;
	std::uniform_real_distribution<float> u;
	int n;
};

