#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/SignalSlot/Signal.h"
#include "ECS/Entity/GameObject.h"
#include "Utils/Logger.h"

#include <iostream>

using SceneManager = frost::core::SceneManager;
using GameObject = frost::ECS::GameObject;
using Transform = frost::ECS::Transform;
using Logger = frost::utils::Logger;

int main()
{
	Logger::LogInfo("Start engine, creating Scene...");

	std::string MainSceneName = "GameScene";
	SceneManager::GetInstance().CreateScene(MainSceneName);
	SceneManager::GetInstance().LoadScene(MainSceneName);

	Logger::LogInfo("Creating GameObjectTest with position (1, 2, 3)...");
	GameObject GameObjectTest = GameObject("GameObjectTest");
	Transform* TransformC = GameObjectTest.GetComponent<Transform>();
	TransformC->position = glm::vec2(1, 2);

	GameObjectTest.AddTag("Tag1");

	GameObjectTest.GetData(true);
	Logger::GetInstance()->Show();

	return 0;
}
