#include "Surface.h"

Surface::Surface(std::shared_ptr<BRDF> brdf, bool isLightSource, const Vector3f &e)
	:brdf(brdf), isLightSource(isLightSource), e(e)
{
}

Surface::~Surface()
{
}
