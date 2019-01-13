#pragma once
#include<vector>
#include<memory>
#include<string>

#include<Surface.h>
#include<Aggregate.h>

class Scene
{
public:
	Scene();
	~Scene();

	void render();
	Vector3f rayTracer(const Ray &ray);
	void saveToImage(const std::string & fileName);
private:
	int width = 600, height = 400;
	std::vector<std::vector<Vector3f>> image;
	std::shared_ptr<Aggregate> aggregates;
};

