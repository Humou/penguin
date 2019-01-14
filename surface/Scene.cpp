#include<random>

#include"Ray.h"
#include "Scene.h"
#include"Sphere.h"
#include"lodepng.h"
#include"Vector3f.h"

Scene::Scene()
{
	aggregates = std::make_shared<Aggregate>();
	std::shared_ptr<Surface> sphere = std::make_shared<Sphere>(Vector3f(0, 0, -0.18), 0.5);
	aggregates->addSurface(sphere);
}

Scene::~Scene()
{
}

void Scene::render()
{
	std::default_random_engine e;
	std::uniform_real_distribution<float> u(0, 1);
	int ns = 10;
	int width = camera.getWidth(), height = camera.getHeight();
	//遍历所有像素，将像素点转换为对应的屏幕坐标，再将屏幕坐标变换到[-1, 1]
	for(int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
			Vector3f color;
			//对同一个像素采样多个点
			for (int i = 0; i < ns; i++) {
				float r1 = 2 * u(e) - 1;
				float r2 = 2 * u(e) - 1;
				float s_x = (x + 0.5) + r1, s_y = (y + 0.5) + r2;
				color += rayTracer(camera.generateRay(s_x, s_y));
			}
			camera.setPixel(y, x, color/ns);
		}

	camera.saveToImage("./output/images/sphere.png");
}

Vector3f Scene::rayTracer(const Ray &ray)
{
	std::shared_ptr<IntersectInfo> info = std::make_shared<IntersectInfo>();
	if (aggregates->interect(ray, info)) {
		return 0.5 * Vector3f(info->normal.x + 1, info->normal.y + 1, info->normal.z + 1);
	}
	else {
		Vector3f unit_direction = Vector3f::normalize(ray.d);
		float t = 0.5 * (unit_direction.y + 1.0);
		return (1 - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5, 0.7, 1.0);
	}
}

