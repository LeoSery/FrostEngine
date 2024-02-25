#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/SignalSlot/Signal.h"
#include "ECS/Entity/GameObject.h"
#include "Utils/Logger.h"
#include "Core/Window.h"
#include "Render/RenderDevice.h"
#include "Core/Window.h"

#include "Render/RenderDevice.h"
#include "Render/Buffer.h"
#include "Render/Texture.h"

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


	//Graphics And Window
	frost::core::Window window({ "Name", glm::ivec2(960, 540) });
	frost::core::RenderDevice _renderDevice(window);

	_renderDevice.test();
	//TEST
	float vertices[] = {
				-0.5f,  0.5f, /*Color*/0.0f, 1.0f,
				-0.5f, -0.5f, /*Color*/0.0f, 0.0f,
				 0.5f, -0.5f, /*Color*/1.0f, 0.0f,
				 0.5f,  0.5f, /*Color*/1.0f, 1.0f,
	};

	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

	frost::core::Buffer VBO(vertices, sizeof(vertices));
	frost::core::Buffer IBO(indices, sizeof(indices));
	frost::core::VertexArrayObject ALED;
	frost::core::VertexArrayObject BALED;



	ALED.BindBuffer(frost::core::VertexArrayObject::eTypeBuffer::VBO, VBO);
	ALED.BindBuffer(frost::core::VertexArrayObject::eTypeBuffer::IBO, IBO);
	_renderDevice.AddVao(ALED);


	BALED.BindBuffer(frost::core::VertexArrayObject::eTypeBuffer::VBO, VBO);
	BALED.BindBuffer(frost::core::VertexArrayObject::eTypeBuffer::IBO, IBO);
	BALED.SetLocation({ 0.5 ,0.2 });
	_renderDevice.AddVao(BALED);

	do
	{
		_renderDevice.AddVao(ALED);
		_renderDevice.AddVao(BALED);
		ALED.SetLocation({ ALED.GetLocation().x + 1.f / 120, 0 });

		_renderDevice.Update();
		ALED.SetLocation({ ALED.GetLocation().x + 1.f / 60,0.2 });


	} while (window.PollEvents());

	return 0;
}
