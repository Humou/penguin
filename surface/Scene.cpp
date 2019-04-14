#include<random>
#include<vector>
#include<thread>
#include<Dielectric.h>
#include"Ray.h"
#include<Plane.h>
#include "Scene.h"
#include"Sphere.h"
#include"lodepng.h"
#include"Vector3f.h"

Scene::Scene()
	:u(0, 1)
{
	aggregates = std::make_shared<Aggregate>();               //center                radius    brdf                          isLight  color    
	//std::shared_ptr<Surface> sphere = std::make_shared<Sphere>(Vector3f(0.4, -0.5, -0.5), 0.3, std::make_shared<ModifiedPhong>(), false, Vector3f(0.4, 0.2, 0.3), Vector3f(30, 30, 30));
	std::shared_ptr<Surface> sphere = std::make_shared<Sphere>(Vector3f(0.4, -0.5, -0.3), 0.2, Material(MAT_TYPE::DIFFUSE, false, Vector3f(0.3, 0.3, 0.3)));
	                                                          //center                 radius    brdf                          isLight color                      emission
	std::shared_ptr<Surface> sphere0 = std::make_shared<Sphere>(Vector3f(-0.45, -0.6, -0.6), 0.3, Material(MAT_TYPE::PERFECT_SPECULAR, false, Vector3f(0.3, 0.3, 0.3)));

	float min_x = -0.9, max_x = 0.9, min_y = -0.9, max_y = 0.9, min_z = -0.9, max_z = 0.6;
	std::vector<Vector3f> vertices = {
		Vector3f(min_x, min_y, max_z), Vector3f(max_x, min_y, max_z), Vector3f(max_x, min_y, min_z), Vector3f(min_x, min_y, min_z),
		Vector3f(min_x, max_y, max_z), Vector3f(max_x, max_y, max_z), Vector3f(max_x, max_y, min_z), Vector3f(min_x, max_y, min_z)
	};
	float step = 0.2;
	Vector3f A = vertices[4], B = vertices[7], C = vertices[6], D = vertices[5];
	Vector3f mid = (A + B + C + D) / 4;
	mid.y -= 0.01;
	Vector3f newA(mid.x - step, mid.y, mid.z + step), newB(mid.x + step, mid.y, mid.z + step),
		     newC(mid.x + step, mid.y, mid.z - step), newD(mid.x - step, mid.y, mid.z - step);

	std::shared_ptr<Surface> light = std::make_shared<Plane>(newA, newB, newC, newD, Material(MAT_TYPE::DIFFUSE, true, Vector3f(0.6, 0.6, 0.6), Vector3f(30, 30, 30)));//light
	
	std::shared_ptr<Surface> topWall = std::make_shared<Plane>(vertices[4], vertices[7], vertices[6], vertices[5], Material());//top
	std::shared_ptr<Surface> bottomWall = std::make_shared<Plane>(vertices[0], vertices[1], vertices[2], vertices[3], Material());//bottom
	std::shared_ptr<Surface> leftWall = std::make_shared<Plane>(vertices[0], vertices[3], vertices[7], vertices[4], Material(MAT_TYPE::DIFFUSE, false, Vector3f(0.4, 0.0, 0.0)));//left
	std::shared_ptr<Surface> rightWall = std::make_shared<Plane>(vertices[1], vertices[5], vertices[6], vertices[2], Material(MAT_TYPE::DIFFUSE, false, Vector3f(0.0, 0.4, 0.0)));//right
	std::shared_ptr<Surface> backWall = std::make_shared<Plane>(vertices[3], vertices[2], vertices[6], vertices[7], Material());//back

	aggregates->addSurface(sphere);
	aggregates->addSurface(sphere0);
	//aggregates->addSurface(sphere1);
	aggregates->addSurface(light);

	aggregates->addSurface(topWall);
	aggregates->addSurface(bottomWall);
	aggregates->addSurface(leftWall);
	aggregates->addSurface(rightWall);
	aggregates->addSurface(backWall);
}

Scene::~Scene()
{
}

void Scene::render()
{
	int cpuCoreNum = std::thread::hardware_concurrency() - 1;
	std::cout << "cpuCoreNum: " << cpuCoreNum << std::endl;
	std::cout << "ns: " << ns << std::endl;
	int blockNum = camera.getHeight()/cpuCoreNum;
	std::vector<std::thread*> threads;

	for (int i = 0; i < cpuCoreNum; i++) {
		int rowStart = i * blockNum;
		int rowEnd = (i + 1) * blockNum;
		if (i == cpuCoreNum - 1) rowEnd = camera.getHeight();
		auto thread = new std::thread(&Scene::caculatePxiel, this, rowStart, rowEnd);
		threads.push_back(thread);
	}

	for (int i = 0; i < cpuCoreNum; i++)
		threads[i]->join();

	std::string fileName = "./output/images/sphere_" + std::to_string(ns) + ".png";
	camera.saveToImage(fileName);
}

Vector3f Scene::pathTracer(const Ray &ray)
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
	std::shared_ptr<IntersectInfo> info = std::make_shared<IntersectInfo>();

	if (aggregates->interect(ray, info)) {
		info->p += 0.001 * info->normal;
		Ray newRay(info->p, info->wi);

		if (depth >= 5) {
			auto colour = info->color;
			double p = colour.x>colour.y && colour.x>colour.z ? colour.x : colour.y>colour.z ? colour.y : colour.z;
			double rnd = u(e);
			if (rnd < p * 0.9) {
				info->color = colour * (0.9 / p);
			}
			else {
				return info->e;
			}
		}
		return info->e + (info->color * Li(newRay, depth + 1));
	}

	return Vector3f(0.2, 0.2, 0.2);
}

void Scene::caculatePxiel(int rowStart, int rowEnd)
{
	std::default_random_engine e;
	std::uniform_real_distribution<float> u(0, 1);
	float exposure = 0.5;
	int regionNum = 4;
	float regionStep = 1.0 / (regionNum);
	int width = camera.getWidth(), height = camera.getHeight();

	for (int y = rowStart; y < rowEnd; y++) {
		for (int x = 0; x < width; x++) {
			Vector3f color;
			float s_x = (x + 0.5), s_y = (y + 0.5);
			float left_x = s_x - (regionStep * regionNum / 2.0), bottom_y = s_y - (regionStep * regionNum / 2.0);
			//stratified sampling
			for (int row = 0; row < regionNum; row++)
				for (int col = 0; col < regionNum; col++) {
					float corner_x = left_x + regionStep * col;
					float corner_y = bottom_y + regionStep * row;
					Vector3f sampleColor;
					for (int i = 0; i < ns; i++) {
						float r1 = u(e), r2 = u(e);
						float sample_x = corner_x + r1 * regionStep, sample_y = corner_y + r2 * regionStep;
						sampleColor += Li(camera.generateRay(sample_x, sample_y)) / ns;
					}

					color += sampleColor;
				}
			color = color / (regionNum * regionNum);
			//tone mapping
			//color = 0 - color * exposure;
			//color = Vector3f(1.0, 1.0, 1.0) - Vector3f(std::exp(color.x), std::exp(color.y), std::exp(color.z));

			color = color / (color + Vector3f(1, 1, 1));
			camera.setPixel(y, x, color);
		}
		if(y % 10 == 0)std::cout << "thread: " << std::this_thread::get_id() << " y: " << y<<" start: "<<rowStart<<" end: "<<rowEnd<<std::endl;
	}
		
		
}

