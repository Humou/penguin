#include<random>
#include<vector>

#include"Ray.h"
#include<Plane.h>
#include "Scene.h"
#include"Sphere.h"
#include"lodepng.h"
#include"Vector3f.h"

Scene::Scene()
{
	aggregates = std::make_shared<Aggregate>();               //center                radius    brdf                          isLight  color    
	std::shared_ptr<Surface> sphere = std::make_shared<Sphere>(Vector3f(0, -0.1, -0.5), 0.3, std::make_shared<ModifiedPhong>(), false, Vector3f(0.8, 0.2, 0.3));
	                                                          //center                 radius    brdf                          isLight color                      emission
	std::shared_ptr<Surface> sphere0 = std::make_shared<Sphere>(Vector3f(-0.4, 0.05, -0.3), 0.1, std::make_shared<ModifiedPhong>(), false, Vector3f(0.1f, 0.3f, 0.8f), Vector3f(0.8, 0.8, 0.8));
	std::shared_ptr<Surface> sphere1 = std::make_shared<Sphere>(Vector3f(0.4, 0.05, -0.3), 0.1, std::make_shared<ModifiedPhong>(), false, Vector3f(0.2f, 0.8f, 0.2f), Vector3f(0.8, 0.8, 0.8));

	float min_x = -0.9, max_x = 0.9, min_y = -0.9, max_y = 0.9, min_z = -0.9, max_z = -0.2;
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
	std::shared_ptr<Surface> topWall = std::make_shared<Plane>(vertices[4], vertices[7], vertices[6], vertices[5], false);//top
	std::shared_ptr<Surface> light = std::make_shared<Plane>(newA, newB, newC, newD);//light
	std::shared_ptr<Surface> bottomWall = std::make_shared<Plane>(vertices[0], vertices[1], vertices[2], vertices[3], false);//bottom
	std::shared_ptr<Surface> leftWall = std::make_shared<Plane>(vertices[0], vertices[3], vertices[7], vertices[4], false);//left
	std::shared_ptr<Surface> rightWall = std::make_shared<Plane>(vertices[1], vertices[2], vertices[6], vertices[5], false);//right
	std::shared_ptr<Surface> backWall = std::make_shared<Plane>(vertices[3], vertices[2], vertices[6], vertices[7], false);//back

	aggregates->addSurface(sphere);
	aggregates->addSurface(sphere0);
	aggregates->addSurface(sphere1);

	aggregates->addSurface(topWall);
	aggregates->addSurface(light);
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
	std::default_random_engine e;
	std::uniform_real_distribution<float> u(0, 1);
	int ns = 100;
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
	if (depth > 3) {
		return Vector3f(0.2, 0.2, 0.2);
		//std::cout << "depth > 3" << std::endl;
		//return Vector3f(0.0, 0.0, 0.0);
	}

	std::shared_ptr<IntersectInfo> info = std::make_shared<IntersectInfo>();

	if (aggregates->interect(ray, info)) {
		info->p += 0.001 * info->wi;
		Ray newRay(info->p, info->wi);
		if (info->f == 0) return info->e;
		//std::cout << "info->e: " << info->e << " info->color: " << info->color << " info->f: " << info->f << " info->pdf: " << info->pdf << std::endl;
		//std::cout << "Li: " << Li(newRay, depth + 1) << std::endl;
		//std::cout <<"oldRay: "<<ray<< " newRay: " << newRay << std::endl;
		//std::cout << "depth: "<<depth<<"info->ID: " << info->ID << std::endl;
		return (info->e + info->color * info->f * Li(newRay, depth + 1) / info->pdf);
	}
   //if(depth > 1)std::cout << "depth: " << depth << std::endl;
	return Vector3f(0.2, 0.2, 0.2);
	//return Vector3f(0.0, 0.0, 0.0);
}

