#include "Dielectric.h"

#include<algorithm>

Dielectric::Dielectric()
	:u(0, 1)
{
}


Dielectric::~Dielectric()
{
}

Vector3f Dielectric::sampleReflect(float & f, float & pdf, Vector3f & normal, Vector3f & w0)
{
	float cosTheta = Vector3f::dot(w0, normal);
	Vector3f newNormal;
	if (cosTheta >= 0)
		newNormal = normal;
	else
		newNormal = 0 - normal;

	Vector3f relect = (0 - w0) + 2 * (Vector3f::dot(w0, newNormal)) * newNormal;
	f = fresnel(relect, newNormal);
	pdf = P;
	return relect;

}

Vector3f Dielectric::sampleRetract(float & f, float & pdf, Vector3f & normal, Vector3f & w0)
{
	Vector3f d = 0 - w0;
	float cosTheta = Vector3f::dot(normal, w0);
	float n = 1;
	Vector3f t;
	//enter sphere
	if (cosTheta >= 0) {
		//Vector3f reflect = (0 - w0) + 2 * (Vector3f::dot(w0, normal)) * normal;
		t = n * (d - normal * Vector3f::dot(d, normal)) / nt - normal * sqrt(1 - n * n * (1 - pow(Vector3f::dot(d, normal), 2)) / pow(nt, 2));
		t.normalize();
		f = 1 - fresnel(t, 0 - normal);
	}
	else //leave sphere
	{
		std::swap(n, nt);
		Vector3f newNormal = 0 - normal;

		//Vector3f reflect = (0 - w0) + 2 * (Vector3f::dot(w0, newNormal)) * newNormal;
		t = n * (d - newNormal * Vector3f::dot(d, newNormal)) / nt - newNormal * sqrt(1 - n * n * (1 - pow(Vector3f::dot(d, newNormal), 2)) / pow(nt, 2));
		t.normalize();
		f = 1 - fresnel(t, 0 - newNormal);
		std::swap(n, nt);
	}

	pdf = 1 - P;
	return t;
}

Vector3f Dielectric::sample(float & f, float & pdf, Vector3f & normal, Vector3f & w0)
{
	normal.normalize();
	w0.normalize();
	float r = u(e);
	if (r <= P)
		return sampleReflect(r, pdf, normal, w0);
	else
		return sampleRetract(r, pdf, normal, w0);
}

float Dielectric::fresnel(Vector3f & w0, Vector3f & n)
{
	w0.normalize();
	n.normalize();
	float cosTheta = Vector3f::dot(w0, n);

	return R0 + (1 - R0) * pow(1 - cosTheta, 5);
}
