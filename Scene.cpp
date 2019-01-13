#include"Ray.h"
#include "Scene.h"
#include"Vector3f.h"

Scene::Scene()
{
	image.resize(height);
	for (int i = 0; i < image.size(); i++) {
		image[i].resize(width);
	}
}

Scene::~Scene()
{
}

void Scene::render()
{
	//±ä»»µ½[-1, 1]
	for(int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
			float x0 = 2.0 / (width - 1) * x - 1.0;
			float y0 = 2.0 / (height - 1) * y - 1.0;
			float z0 = -0.5;
			Vector3f origin(0, 0, 0);
			Vector3f pos(x0, y0, z0);
			Ray ray(origin, (pos - origin));

		}
}
