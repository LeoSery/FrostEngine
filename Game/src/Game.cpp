#include "FrostEngine.h"
#include "TestInput.h"

#pragma region "Alias"
using SpriteRenderer = frost::ECS::SpriteRenderer;
using SceneManager = frost::core::SceneManager;
using GameObject = frost::ECS::GameObject;
using Transform = frost::ECS::Transform;
using Logger = frost::utils::Logger;
#pragma endregion

class MyGameApp : public FrostEngine::Application
{
public:
	void Init() override
	{
		std::string MainSceneName = "GameScene";
		SceneManager::GetInstance().CreateScene(MainSceneName);
		SceneManager::GetInstance().LoadScene(MainSceneName);
		Application::Init({ "Mon super jeu", glm::ivec2(1600, 900) });


		GameObject* GameObjectTest = GameObject::New("GameObjectTest");
		Transform* TransformC = GameObjectTest->GetComponent<Transform>();
		TransformC->position = glm::vec2(0, 0);

		GameObjectTest->AddComponent<SpriteRenderer>();
		SpriteRenderer* SpriteRendererC = GameObjectTest->GetComponent<SpriteRenderer>();
		SpriteRendererC->SetTexture("T_Debug_Quad.png");

		GameObjectTest->AddTag("Tag1");
		GameObjectTest->AddTag("Tag2");

		GameObject* GameObjectTest2 = GameObject::New("GameObjectTest2");
		Transform* TransformC2 = GameObjectTest2->GetComponent<Transform>();
		TransformC2->position = glm::vec2(0.5, 0);

		GameObjectTest->GetData(true);
		GameObjectTest2->GetData(true);

		TestInput* Test = TestInput::New("Hehe");
		Test->Begin();

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
