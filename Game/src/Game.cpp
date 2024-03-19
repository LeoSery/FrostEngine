#include "FrostEngine.h"

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
	GameObject* GameObjectTest;
	GameObject* GameObjectTest2;

	void Init() override
	{
		// Game Setup
		std::string MainSceneName = "GameScene";
		SceneManager::GetInstance().CreateScene(MainSceneName);
		SceneManager::GetInstance().LoadScene(MainSceneName);
		Application::Init({ "Mon super jeu", glm::ivec2(1600, 900) });
		Logger::LogInfo("Creating 2 GameObjects and set their pos");

		// Create GameObjects
		// GameObject 1
		GameObjectTest = new GameObject("GameObjectTest");
		GameObjectTest->AddComponent<SpriteRenderer>();
		GameObjectTest->AddComponent<BoxCollider>();

		Transform* TransformC = GameObjectTest->GetComponent<Transform>();
		TransformC->position = glm::vec2(0, 0);

		SpriteRenderer* SpriteRendererC = GameObjectTest->GetComponent<SpriteRenderer>();
		SpriteRendererC->SetTexture("T_Debug_Quad.png");

		BoxCollider* BoxColliderC = GameObjectTest->GetComponent<BoxCollider>();
		BoxColliderC->SetIsStatic(true);

		GameObjectTest->AddTag("Tag1");
		GameObjectTest->AddTag("Tag2");

		// GameObject 2
		GameObjectTest2 = new GameObject("GameObjectTest2");
		GameObjectTest2->AddComponent<SpriteRenderer>();
		GameObjectTest2->AddComponent<BoxCollider>();

		Transform* TransformC2 = GameObjectTest2->GetComponent<Transform>();
		TransformC2->position = glm::vec2(0.5, 0);

		SpriteRenderer* SpriteRendererC2 = GameObjectTest2->GetComponent<SpriteRenderer>();
		SpriteRendererC2->SetTexture("T_DebugHolder.png");

		// Debug Data
		GameObjectTest->GetData(true);
		GameObjectTest2->GetData(true);
	}

	void Update(float deltaTime) override
	{
		auto* tmp = GameObjectTest->GetComponent<BoxCollider>();
		bool IsColliding = GameObjectTest2->GetComponent<BoxCollider>()->IsColliding(*tmp);
		Logger::LogInfo("IsColliding : " + std::to_string(IsColliding));

		(void)deltaTime; //this is to avoid warning when delta time is not used
		// To do : update game logic (one frame)
	}

	void Shutdown() override
	{
		Application::Shutdown();
	}
};

FROST_APPLICATION(MyGameApp)
