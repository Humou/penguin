#include<random>

#include"Ray.h"
#include "Scene.h"
#include"Sphere.h"
#include"lodepng.h"
#include"Vector3f.h"

Scene::Scene()
{
	aggregates = std::make_shared<Aggregate>();
	std::shared_ptr<Surface> sphere = std::make_shared<Sphere>(Vector3f(0, 0, -0.18), 0.5, std::make_shared<ModifiedPhong>(), true, Vector3f(0.8, 0.2, 0.3));

	std::shared_ptr<Surface> light = std::make_shared<Sphere>(Vector3f(0, 0.2, -0.3), 0.2, std::make_shared<ModifiedPhong>(), true, Vector3f(1.0f, 1.0f, 1.0f), Vector3f(0.5, 0.5, 0.5));
	aggregates->addSurface(sphere);
	aggregates->addSurface(light);
}

Scene::~Scene()
{
}

void Scene::render()
{
	std::default_random_engine e;
	std::uniform_real_distribution<float> u(0, 1);
	int ns = 5;
	int width = camera.getWidth(), height = camera.getHeight();
	//遍历所有像素，将像素点转换为对应的屏幕坐标，再将屏幕坐标变换到[-1, 1]
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) {
			Vector3f color;
			//对同一个像素采样多个点
			for (int i = 0; i < ns; i++) {
				float r1 = 2 * u(e) - 1;
				float r2 = 2 * u(e) - 1;
				float s_x = (x + 0.5) + r1, s_y = (y + 0.5) + r2;
				color += Li(camera.generateRay(s_x, s_y));
			}
			camera.setPixel(y, x, color / ns);
			//std::cout << color<<std::endl;
		}
		std::cout << "y: " << y << std::endl;
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
		Vector3f unit_direction  = ray.d;
		unit_direction.normalize();
		float t = 0.5 * (unit_direction.y + 1.0);
		return (1 - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5, 0.7, 1.0);
	}
}

Vector3f Scene::Li(const Ray & ray, int depth)
{
	if (depth > 3) return Vector3f(0, 0, 0);

	std::shared_ptr<IntersectInfo> info = std::make_shared<IntersectInfo>();
	if (aggregates->interect(ray, info)) {
		Ray newRay(info->p, info->wi);
		if (info->f == 0) return info->e;
		
		return (info->e + info->color * info->f * Li(newRay, depth + 1) / info->pdf);
	}
	return Vector3f(0, 0, 0);
}

