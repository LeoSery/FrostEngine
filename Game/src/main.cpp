#include "ECS/Entity/GameObject.h"
#include "Core/SceneManager.h"
#include "Core/Scene.h"

#include <iostream>

using namespace frost;

using GameObject = frost::ECS::GameObject;
using Transform = frost::core::Transform;

int main() 
{
	std::cout << "Start engine, creating Scene..." << std::endl;

	std::string MainSceneName = "GameScene";
	core::SceneManager::GetInstance().CreateScene(MainSceneName);
	core::SceneManager::GetInstance().LoadScene(MainSceneName);

	std::cout << "Creating GameObjectTest with position (1, 2, 3)..." << std::endl;
	GameObject GameObjectTest = GameObject("GameObjectTest");
	GameObjectTest.SetTransform(Transform({1,1}, {}, {1,1}));

	GameObjectTest.AddTag("Tag1");

	GameObjectTest.GetData(std::cout);

	return 0;
}