#include "ECS/GameObject.h"

#include <iostream>

using namespace frost;

int main() 
{
	std::cout << "Start engine, creating SceneRoot..." << std::endl;
	ECS::GameObject SceneRoot = ECS::GameObject("SceneRoot");

	std::cout << "Creating GameObjectTest with position (1, 2, 3)..." << std::endl;
	ECS::GameObject GameObjectTest = ECS::GameObject("GameObjectTest", &SceneRoot);
	GameObjectTest.SetTransform(core::Transform({1,1,1}, {}, {1,1,1}));

	GameObjectTest.AddTag("Tag1");

	GameObjectTest.GetData(std::cout);

	return 0;
}