#include "Surface.h"

int Surface::curID = 0;
Surface::Surface(std::shared_ptr<BRDF> brdf, bool isLightSource, const Vector3f &color, const Vector3f &e)
	:brdf(brdf), isLightSource(isLightSource), color(color), e(e)
{
	ID = curID++;
}

Surface::~Surface()
{
}
