// Engine includes
#include "FrostEngine.h"

// Game includes
#include "Player.h"
#include "Ennemi.h"
#include <Spawner.h>

#pragma region "Alias"
using SceneManager = frost::core::SceneManager;
using GameObject = frost::ECS::GameObject;
using Transform = frost::ECS::Transform;
using Logger = frost::utils::Logger;
#pragma endregion

class MyGameApp : public frost::Application
{
public:
	GameObject* PlayerEntity = nullptr;
	Spawner* Spawner = nullptr;

	void Init() override
	{
		//// Game Setup
		// Scene
		std::string MainSceneName = "GameScene";
		SceneManager::GetInstance().CreateScene(MainSceneName);
		SceneManager::GetInstance().LoadScene(MainSceneName);
		Application::Init({ "Mon super jeu", glm::ivec2(1600, 900) });

		// Player
		PlayerEntity = Player::New("Player", m_CurrentScene->GetRoot());
		Transform* PlayerTransform = PlayerEntity->GetComponent<Transform>();
		PlayerTransform->position = glm::vec2(-6, 0);

		// Spawner
		Spawner = Spawner::New("Spawner", {0,3} , m_CurrentScene->GetRoot() ,PlayerEntity);
		
	}

	void Update(float deltaTime) override
	{
		(void)deltaTime; //this is to avoid warning when delta time is not used
		// To do : update game logic (one frame)
	}

	void Shutdown() override
	{
		Application::Shutdown();
	}
};

FROST_APPLICATION(MyGameApp)
