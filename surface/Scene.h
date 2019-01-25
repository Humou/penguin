#pragma once
#include<vector>
#include<memory>
#include<string>

#include<Camera.h>
#include<Surface.h>
#include<Aggregate.h>

class Scene
{
public:
	Scene();
	~Scene();

	void render();
	Vector3f rayTracer(const Ray &ray);
	Vector3f Li(const Ray &ray, int depth = 0);
private:
	std::shared_ptr<Aggregate> aggregates;
	Camera camera;
};

