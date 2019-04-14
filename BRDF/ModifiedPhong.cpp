#include<algorithm>
#include "ModifiedPhong.h"



ModifiedPhong::ModifiedPhong()
	:u(0, 1), p_d(0.1), p_s(0.9), k_s(0.6),n(10)
{
}


ModifiedPhong::~ModifiedPhong()
{
}

Vector3f ModifiedPhong::sample(float &f, float &pdf, Vector3f &normal, Vector3f &wo)
{
	return sampleDiffuse(f, pdf, normal, wo);
	//float r = u(e);
	//if (0 <= r && r < p_d) return sampleDiffuse(f, pdf, normal, wo);
	//else if (p_d <= r && r < p_d + p_s) return sampleSpecular(f, pdf, normal, wo);
	
	//return sampleDiffuse(f, pdf, normal, wo);
	
}

Vector3f ModifiedPhong::sampleDiffuse(float &f, float &pdf, Vector3f &normal, Vector3f &wo)
{
	float r1 = u(e), r2 = u(e);
	float x = sqrtf(1 - r1) * cos(2 * PI * r2);
	float y = sqrtf(1 - r1) * sin(2 * PI * r2);
	float z = sqrtf(r1);
	Vector3f wi;
	Vector3f w = normal;
	w.normalize();
	float minIndex = std::abs(w.x) < std::abs(w.y) ? 0 : 1;
	minIndex = std::abs(w[minIndex]) < std::abs(w.z) ? minIndex : 2;
	Vector3f t = w;
	t[minIndex] = 1;

	Vector3f u = Vector3f::cross(t, w);
	u.normalize();
	Vector3f v = Vector3f::cross(w, u);

	wi.x = u.x * x + v.x * y + w.x * z;
	wi.y = u.y * x + v.y * y + w.y * z;
	wi.z = u.z * x + v.z * y + w.z * z;
	wi.normalize();

	//computer brdf pdf
	float costheta = std::max(Vector3f::dot(normal, wi), 0.0f);
	f = (1 / PI) * costheta;
	pdf = p_d * f;
	return wi;
}

Vector3f ModifiedPhong::sampleSpecular(float &f, float &pdf, Vector3f &normal, Vector3f &wo)
{
	float r1 = u(e), r2 = u(e);
	float vf = sqrtf( 1 - pow(r1, 2.0 / (n + 1)) );
	float x = vf * cos(2 * PI * r2);
	float y = vf * sin(2 * PI * r2);
	float z = pow(r1, 1.0 / (n + 1));
	Vector3f wi;
	//transform vector to world coordinate
	Vector3f w = normal;
	w.normalize();
	float minIndex = std::abs(w.x) < std::abs(w.y) ? 0 : 1;
	minIndex = std::abs(w[minIndex]) < std::abs(w.z) ? minIndex : 2;
	Vector3f t = w;
	t[minIndex] = 1;

	Vector3f u = Vector3f::cross(t, w);
	u.normalize();
	Vector3f v = Vector3f::cross(w, u);

	wi.x = u.x * x + v.x * y + w.x * z;
	wi.y = u.y * x + v.y * y + w.y * z;
	wi.z = u.z * x + v.z * y + w.z * z;
	wi.normalize();

	Vector3f reflect = 2 * Vector3f::dot(wo, normal) * normal - wo;
	reflect.normalize();

	float cosalpha = std::max(Vector3f::dot(wo, reflect), 0.0f);
	float costheta = std::max(Vector3f::dot(normal, wi), 0.0f);
	f = k_s * ((n + 2.0) / 2 * PI) * pow(cosalpha, n) * cosalpha;
	pdf = ((n + 1.0) / 2 * PI) * pow(cosalpha, n);

	wi = reflect;
	return wi;
}
