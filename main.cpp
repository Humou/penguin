#include<memory>
#include<iostream>

#include"Scene.h"
int main() {
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	scene->render();
	scene->saveToImage("./images/sphere.png");
	return 0;
}