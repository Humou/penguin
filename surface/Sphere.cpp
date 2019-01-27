#include<cmath>

#include "Sphere.h"
Sphere::~Sphere()
{

}

bool Sphere::interect(const Ray & ray, std::shared_ptr<IntersectInfo> info)
{
	Vector3f oc = ray.o - center;
	float a = Vector3f::dot(ray.d, ray.d);
	float b = 2.0 * Vector3f::dot(oc, ray.d);
	float c = Vector3f::dot(oc, oc) - r * r;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return false;
	float t;
	if (discriminant == 0) {
		t = (-b + sqrt(discriminant)) / (2 * a);
	}
	else {
		t = (-b - sqrt(discriminant)) / (2 * a);
		auto t2 = (-b + sqrt(discriminant)) / (2 * a);
		if (t2 > 0 && t2 < t) {
			t = t2;
		}
	}

	if (t <= 1e-5) return false;

	if (info->isValid & t >= info->t) return true;
	//��ǰ����Ϊ���������һ�����㣬����Ҫ�ı�info
	info->p = ray.evaluate(t);
	info->t = t;
	info->isValid = true;
	info->normal = (info->p - center);
	info->normal.normalize();
	info->color = color;
	if (isLight()) {
		info->isLightSource = true;
		info->e = getEmision();
	}
	//std::cout << "ray.o: " << ray.o << " ray.d: " << ray.d << std::endl;
	//std::cout << "info->p: " << info->p << " center: " << center<<std::endl;
	//std::cout << "normal: " << info->normal << std::endl;
	brdf->sample(info->f, info->pdf, info->normal, Vector3f::normalized(ray.d));
	return true;
}
