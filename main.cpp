#include<memory>
#include<iostream>

#include<Scene.h>
int main() {
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	scene->render();

	system("pause");
	return 0;
}