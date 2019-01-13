#pragma once
#include<vector>
#include<memory>

#include"Surface.h"
class Aggregate : public Surface
{
public:
	Aggregate();
	~Aggregate();
	bool interect(const Ray &ray, std::shared_ptr<IntersectInfo> info) override;
	void addSurface(const std::shared_ptr<Surface> &surface);
private:
	std::vector<std::shared_ptr<Surface>> aggregates;
	
};

