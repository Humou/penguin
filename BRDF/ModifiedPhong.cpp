#include "ModifiedPhong.h"



ModifiedPhong::ModifiedPhong()
	:u(0, 1), p_d(0.4), p_s(0.4), k_s(0.2)
{
}


ModifiedPhong::~ModifiedPhong()
{
}

Vector3f ModifiedPhong::sample(float &f, float &pdf, const Vector3f &normal, const Vector3f &wo)
{
	float r = u(e);
	if (0 <= r && r < p_d) return sampleDiffuse(f, pdf, normal, wo);
	if (p_d <= r && r < p_d + p_s) return sampleSpecular(f, pdf, normal, wo);

	f = 0;
	return Vector3f();
}

Vector3f ModifiedPhong::sampleDiffuse(float &f, float &pdf, const Vector3f &normal, const Vector3f &wo)
{
	float r1 = u(e), r2 = u(e);
	float x = sqrtf(1 - r1) * cos(2 * PI * r2);
	float y = sqrtf(1 - r1) * sin(2 * PI * r2);
	float z = sqrtf(r1);
	//normal.normalize();

	Vector3f wi(x, y, z);
	wi.normalize();

	float costheta = Vector3f::dot(normal, wi);
	f = 1 / PI * costheta;
	pdf = p_d * f;
	return wi;
}

Vector3f ModifiedPhong::sampleSpecular(float &f, float &pdf, const Vector3f &normal, const Vector3f &wo)
{
	float r1 = u(e), r2 = u(e);
	float v = sqrtf( 1 - pow(r1, 2.0 / (n + 1)) );
	float x = v * cos(2 * PI * r2);
	float y = v * sin(2 * PI * r2);
	float z = pow(r1, 1.0 / (n + 1));
	Vector3f wi(x, y, z);

	wi.normalize();
	//normal.normalize();
	//wo.normalize();
	Vector3f reflect = 2 * Vector3f::dot(normal, wi) * normal - wi;

	float cosalpha = Vector3f::dot(0.0 - wo, reflect);
	float costheta = Vector3f::dot(normal, wi);
	f = k_s * (n + 2.0) / 2 * PI * pow(cosalpha, n) * cosalpha;
	pdf = (n + 1.0) / 2 * PI * pow(cosalpha, n);
	return wi;
}
