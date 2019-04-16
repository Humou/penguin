#include <Camera.h>
#include<lodepng.h>
Camera::Camera()
	: origin(0, 0.0, 0.4), zNear(-0.15),
	  min_x(-0.92), max_x(0.92), min_y(-0.92), max_y(0.92)
{
	image.resize(height);
	for (int i = 0; i < image.size(); i++) {
		image[i].resize(width);
	}
}


Camera::~Camera()
{
}

Ray Camera::generateRay(float s_x, float s_y)
{
	float x0 = (max_x - min_x) / (width - 1) * s_x + min_x;
	float y0 = (max_y - min_y) / (height - 1) * s_y + min_y;
	Vector3f pos(x0, y0, zNear);
	Ray ray(origin, (pos - origin));
	return ray;
}

void Camera::setPixel(int y, int x, const Vector3f & color)
{
	image[y][x] = color;
}

void Camera::saveToImage(const std::string & fileName)
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
