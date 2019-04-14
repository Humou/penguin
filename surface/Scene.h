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
	Vector3f pathTracer(const Ray &ray);
	Vector3f Li(const Ray &ray, int depth = 0);

private:
	void caculatePxiel(int rowStart, int rowEnd);
private:
	Camera camera;
	std::shared_ptr<Aggregate> aggregates;

	int ns = 1;
	std::default_random_engine e;
	std::uniform_real_distribution<float> u;
};

