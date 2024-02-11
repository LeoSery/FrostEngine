#include "Core/SceneManager.h"
#include "ECS/GameObject.h"
#include "Core/Scene.h"

#include <iostream>

using namespace frost;

int main() 
{
	std::cout << "Start engine, creating Scene..." << std::endl;

	core::SceneManager::GetInstance().AddScene(core::Scene("GameScene"));
	core::SceneManager::GetInstance().LoadScene("GameScene");

	std::cout << "Creating GameObjectTest with position (1, 2, 3)..." << std::endl;
	ECS::GameObject GameObjectTest = ECS::GameObject("GameObjectTest");
	GameObjectTest.SetTransform(core::Transform({1,1,1}, {}, {1,1,1}));

	GameObjectTest.AddTag("Tag1");

	GameObjectTest.GetData(std::cout);

	return 0;
}