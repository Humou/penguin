#include<algorithm>
#include "ModifiedPhong.h"



ModifiedPhong::ModifiedPhong()
	:u(0, 1), p_d(0.6), p_s(0.4), k_s(0.2),n(10)
{
}


ModifiedPhong::~ModifiedPhong()
{
}

Vector3f ModifiedPhong::sample(float &f, float &pdf, const Vector3f &normal, const Vector3f &wo)
{
	float r = u(e);
	if (0 <= r && r < p_d) return sampleDiffuse(f, pdf, normal, wo);
	else if (p_d <= r && r < p_d + p_s) return sampleSpecular(f, pdf, normal, wo);
	else
	{
		std::cout <<"r: "<<r<< " three" << std::endl;
	}
	//f = 0;
	//if()
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

	float costheta = std::max(Vector3f::dot(normal, wi), 0.0f);
	f = (1 / PI) * costheta;
	pdf = p_d * f;
	if (std::isnan(f)) {
		//std::cout << "wi: " << wi << std::endl;
		//std::cout << "diffuse f: " << f << std::endl;
		//std::cout << "1/PI:" << 1 / PI << std::endl;
		//std::cout << "costheta: " << costheta << std::endl;
	}
	//if (std::isnan(pdf)) std::cout << "diffuse pdf: " << pdf << std::endl;
	//if(std::isnan(wi.x) || std::isnan(wi.y) || std::isnan(wi.z))std::cout << "diffuse wi: " << wi << std::endl;

	wi.x = wi.x + normal.x * wi.y;
	wi.y = normal.y * wi.y;
	wi.z = normal.z * wi.y + wi.z;
	//wi = normal;
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

	Vector3f reflect = 2 * Vector3f::dot(normal, wi) * normal - wi;

	float cosalpha = std::max(Vector3f::dot(0 - wo, reflect), 0.0f);
	float costheta = std::max(Vector3f::dot(normal, wi), 0.0f);
	f = k_s * ((n + 2.0) / 2 * PI) * pow(cosalpha, n) * cosalpha;
	pdf = ((n + 1.0) / 2 * PI) * pow(cosalpha, n);

	//if (std::isnan(f)) std::cout << "specular f: " << f << std::endl;
	//if (std::isnan(pdf)) std::cout << "specular pdf: " << pdf << std::endl;
	//if (std::isnan(wi.x) || std::isnan(wi.y) || std::isnan(wi.z))std::cout << "specualr wi: " << wi << std::endl;
	wi.x = wi.x + normal.x * wi.y;
	wi.y = normal.y * wi.y;
	wi.z = normal.z * wi.y + wi.z;
	//wi = normal;
	return wi;
}
