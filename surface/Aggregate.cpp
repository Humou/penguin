#include "Aggregate.h"

Aggregate::Aggregate()
	:Surface(Material())
{
}

Aggregate::~Aggregate()
{
}

bool Aggregate::interect(const Ray & ray, std::shared_ptr<IntersectInfo> info)
{
	info->isValid = false; 
	for (auto surface : aggregates) {
		surface->interect(ray, info);
	}
	return info->isValid;
}

void Aggregate::addSurface(const std::shared_ptr<Surface>& surface)
{
	aggregates.push_back(surface);
}
