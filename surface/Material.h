#pragma once
#include<random>
#include<BRDF.h>
#include<Vector3f.h>
//const double PI = 3.14159265;
enum class MAT_TYPE {
	PERFECT_SPECULAR,
	GLOSS_SPECULAR,
	DIFFUSE,
	DIELECTRIC,
};
class Material
{
public:
	Material(MAT_TYPE type = MAT_TYPE::DIFFUSE, bool isLight = false, Vector3f color = Vector3f(0.3, 0.3, 0.3), Vector3f emission = Vector3f(50, 50, 50));
	~Material();
	Vector3f sampleDirection(Vector3f & normal, Vector3f & w0);
	Vector3f sampleDiffuse(Vector3f &normal);
	Vector3f samplePerfectSpecular(Vector3f &normal, Vector3f &w0);
	Vector3f sampleGlossSpecular(Vector3f &normal, Vector3f &w0);
	Vector3f sampleDielectric(Vector3f &normal, Vector3f &w0);
	float schlick(float cosTheta);

	std::default_random_engine e;
	std::uniform_real_distribution<float> u;

	float R0 = 0.8;
	float prob = 0.3;
	float n1 = 1;

	bool isLight = false;
	Vector3f color;
	Vector3f emission;
	MAT_TYPE type;
};

