#include"Ray.h"
#include "Scene.h"
#include"Sphere.h"
#include"lodepng.h"
#include"Vector3f.h"

Scene::Scene()
{
	image.resize(height);
	for (int i = 0; i < image.size(); i++) {
		image[i].resize(width);
	}
	aggregates = std::make_shared<Aggregate>();
	std::shared_ptr<Surface> sphere = std::make_shared<Sphere>(Vector3f(0, 0, -0.3), 0.5);
	aggregates->addSurface(sphere);
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
			float z0 = 0.0;
			Vector3f origin(0, 0, 0.4);
			Vector3f pos(x0, y0, z0);
			Ray ray(origin, (pos - origin));
			Vector3f color = rayTracer(ray);
			image[y][x] = color;
		}
	//saveToImage("./sphere.png");
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

void Scene::saveToImage(const std::string & fileName)
{
	unsigned char* data = new unsigned char[width * height * 4];
	unsigned x, y;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			data[4 * width * y + 4 * x + 0] = unsigned char(image[height - 1 - y][x].x * 255);
			data[4 * width * y + 4 * x + 1] = unsigned char(image[height - 1 - y][x].y * 255);
			data[4 * width * y + 4 * x + 2] = unsigned char(image[height - 1 - y][x].z * 255);
			data[4 * width * y + 4 * x + 3] = 255;
		}

	/*Encode the image*/
	unsigned error = lodepng_encode32_file(fileName.c_str(), data, width, height);

	/*if there's an error, display it*/
	if (error) printf("error %u: %s\n", error, lodepng_error_text(error));

	free(data);

}
