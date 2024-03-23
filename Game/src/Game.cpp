// Engine includes
#include "FrostEngine.h"

// Game includes
#include "Player.h"

#pragma region "Alias"
using SpriteRenderer = frost::ECS::SpriteRenderer;
using SceneManager = frost::core::SceneManager;
using BoxCollider = frost::ECS::BoxCollider;
using GameObject = frost::ECS::GameObject;
using Transform = frost::ECS::Transform;
using Logger = frost::utils::Logger;
#pragma endregion

class MyGameApp : public FrostEngine::Application
{
public:
	GameObject* PlayerEntity = nullptr;
	GameObject* Enemy = nullptr;

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
		SpriteRenderer* PlayerSpriteRenderer = PlayerEntity->AddComponent<SpriteRenderer>();
		PlayerSpriteRenderer->SetTexture("T_Debug_Quad.png");

		BoxCollider* BoxColliderComponent = PlayerEntity->AddComponent<BoxCollider>();
		BoxColliderComponent;

		Transform* PlayerTransform = PlayerEntity->GetComponent<Transform>();
		PlayerTransform->position = glm::vec2(-0.6, 0);

		PlayerEntity->GetData(true);

		// Enemy
		Enemy = GameObject::New("Enemy", m_CurrentScene->GetRoot());
		SpriteRenderer* EnemySpriteRenderer = Enemy->AddComponent<SpriteRenderer>();
		EnemySpriteRenderer->SetTexture("T_Debug_Quad.png");

		BoxCollider* EnemyBoxCollider = Enemy->AddComponent<BoxCollider>();
		EnemyBoxCollider;

		Transform* EnemyTransform = Enemy->GetComponent<Transform>();
		EnemyTransform->position = glm::vec2(0.6, 0);

		Enemy->GetData(true);
	}

	void Update(float deltaTime) override
	{

		//PlayerEntity->GetComponent<Transform>()->GetData(true);

		(void)deltaTime; //this is to avoid warning when delta time is not used
		// To do : update game logic (one frame)
	}

	void Shutdown() override
	{
		Application::Shutdown();
	}
};

FROST_APPLICATION(MyGameApp)
