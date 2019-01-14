#pragma once
#include<random>

#include<Ray.h>
#include<Vector3f.h>

class Camera
{
public:
	Camera();
	~Camera();
	Ray generateRay(float s_x, float s_y);
	int getWidth()const { return width; }
	int getHeight() const { return height; }
	void setPixel(int y, int x, const Vector3f& color);
	void saveToImage(const std::string & fileName);
private:
	int width = 600, height = 400;
	std::vector<std::vector<Vector3f>> image;
	Vector3f origin;

	float zNear;
};

