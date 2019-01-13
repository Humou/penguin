#pragma once
#include<vector>

#include"Shape.h"

class Scene
{
public:
	Scene();
	~Scene();

	void render();

private:
	int width = 600, height = 400;
	std::vector<std::vector<unsigned char>> image;
	std::vector<Shape*> shapes;
};

