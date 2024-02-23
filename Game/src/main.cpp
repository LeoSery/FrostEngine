#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/SignalSlot/Signal.h"
#include "ECS/Entity/GameObject.h"
#include "Utils/Logger.h"
#include "Core/Window.h"
#include "Render/RenderDevice.h"

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
				-0.5f,  0.5f, /*Color*/0.5f, 0.0f, 0.0f,
				-0.5f, -0.5f, /*Color*/0.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, /*Color*/0.5f, 1.0f, 0.0f,
				 0.5f,  0.5f, /*Color*/1.0f, 0.8f, 1.0f
	};

	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

	unsigned int buffers[2];
	/*buffer[0] = vertices data	== VBO <- I WAS LOOKING FOR IT , IM SO DUMB SMH
	  buffer[1] = indices data	== IBO		*/

	glCreateBuffers(2, buffers); //Hey open gl i need 2 IDS to store things
	glNamedBufferStorage(buffers[0], sizeof(vertices), vertices, 0); //Buffer 0 = VBO
	glNamedBufferStorage(buffers[1], sizeof(indices), indices, 0);


	frost::core::VertexArrayObject ALED(buffers);
	frost::core::VertexArrayObject BALED(buffers);
	_renderDevice.AddVao(ALED); 

	do
	{
		_renderDevice.AddVao(ALED);

		_renderDevice.Update();
		ALED.SetLocation({ ALED.GetLocation().x + 1.f/60,0.2});


	} while (window.PollEvents());

	return 0;
}
