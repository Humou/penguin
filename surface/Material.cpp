#include "Material.h"

Material::Material(MAT_TYPE type, bool isLight, Vector3f color, Vector3f emission)
	:u(0, 1),type(type),isLight(isLight), color(color), emission(emission)
{
}

Material::~Material()
{
}

Vector3f Material::sampleDirection(Vector3f & normal, Vector3f & w0)
{
	normal.normalize();
	w0.normalize();
	if (type == MAT_TYPE::DIFFUSE) {
		return sampleDiffuse(normal);
	}
	else if (type == MAT_TYPE::PERFECT_SPECULAR) {
		return samplePerfectSpecular(normal, w0);
	}
	else if (type == MAT_TYPE::GLOSS_SPECULAR) {
		return sampleGlossSpecular(normal, w0);
	}
	else if (type == MAT_TYPE::DIELECTRIC) {
		auto wi = sampleDielectric(normal, w0);
		return wi;
	}
}

Vector3f Material::sampleDiffuse(Vector3f & normal)
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

	return wi;
}

Vector3f Material::samplePerfectSpecular(Vector3f & normal, Vector3f & w0)
{
	Vector3f wi = (0 - w0) - normal * 2 * Vector3f::dot(normal,  0-w0);
	wi.normalize();
	//float R = schlick(Vector3f::dot(wi, normal));
	//color = Vector3f(R, R, R);
	if (Vector3f::dot(wi, normal) < 0) {
		//std::cout << "dot(normal, wo): "<<Vector3f::dot(normal, 0 - w0) << std::endl;
	}
	return wi;
}

Vector3f Material::sampleGlossSpecular(Vector3f & normal, Vector3f & w0)
{
	int n = 100;
	float r1 = u(e), r2 = u(e);
	float vf = sqrtf(1 - pow(r1, 2.0 / (n + 1)));
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

	float R = schlick(Vector3f::dot(wi, normal));
	color = Vector3f(R, R, R);
	return wi;
}

Vector3f Material::sampleDielectric(Vector3f & normal, Vector3f & w0)
{
	if (u(e) <= prob) {
		//std::cout << "reflect" << std::endl;
		float cosTheta = Vector3f::dot(normal, w0);

		if (cosTheta >= 0)
		{
			Vector3f wi = (0 - w0) - normal * 2 * Vector3f::dot(normal, 0 - w0);
			wi.normalize();
			float R = schlick(Vector3f::dot(w0, normal));
			color = Vector3f(R, R, R) / prob;
			return wi;
		}
		else {
			Vector3f N = 0 - normal;
			Vector3f wi = (0 - w0) - N * 2 * Vector3f::dot(N, 0 - w0);
			wi.normalize();
			float R = schlick(Vector3f::dot(w0, N));
			color = Vector3f(R, R, R) / prob;
			return wi;
		}
		
	}
	else {
		Vector3f L = 0 - w0;
		float R;
		float cosTheta = Vector3f::dot(normal, w0);
		float n2 = 1.5;
		Vector3f t;
		//enter sphere
		if (cosTheta >= 0) {
			float n0 = n2 / n1;
			float cosTheta1 = Vector3f::dot(w0, normal);
			float cosTheta2 = sqrt(1 - (1 / n0 * n0) * (1 - cosTheta1 * cosTheta1));
			t = 1/n0 * (L + normal * cosTheta1) - normal * cosTheta2;
			t.normalize();
			R = 1 - schlick(Vector3f::dot(w0, normal));
		}
		else //leave sphere
		{
			std::swap(n1, n2);
			float n0 = n2 / n1;
			Vector3f N = 0 - normal;
			float cosTheta1 = Vector3f::dot(w0, N);
			float cosTheta2 = sqrt(1 - (1 / n0 * n0) * (1 - cosTheta1 * cosTheta1));
			t = 1 / n0 * (L + N * cosTheta1) - N * cosTheta2;
			t.normalize();
			R = 1 - schlick(Vector3f::dot(w0, N));
			std::swap(n1, n2);
		}
		color = Vector3f(R, R, R) / (1.0 - prob);
		return t;
	}
}

float Material::schlick(float cosTheta)
{
	return R0 + (1 - R0) * pow(1 - cosTheta, 5);
}
