#pragma once

/*!
* \file FrostEngine.cpp
* 
* \brief Main file for the FrostEngine.
*
* \details This file contains the main methods for the FrostEngine, such as the engine's initialization, main loop and shutdown.
* It also contains the methods for updating GameObjects, physics and rendering.
*/

#include "ECS/Component/Components/SpriteRenderer.h"
#include "ECS/Component/Components/BoxCollider.h"

#include "Core/SceneManagement/SceneManager.h"
#include "Core/Window.h"
#include "Core/Export.h"

#include "Render/RenderDevice.h"
#include "Render/RenderDevice.h"

#include "Editor/Editor.h"

#include "Utils/Logger.h"

#include <chrono>
#include <thread>

/*!
 * \namespace FrostEngine
 *
 * \brief The main namespace for the FrostEngine.
 *
 * \details FrostEngine is the engine's main namespace and contains the engine's
 * update loop for updating GameObjects, physics and OpenGL rendering.
 */
namespace FrostEngine
{
	/*
	* \class Application
	* \brief Main engine class that initializes/shuts down the different engine modules,
	* runs the main loop for updating physics, GameObjects and rendering,
	* and all the components on which they depend.
	*/
	class FROST_ENGINE_API Application
	{
	protected:
		frost::core::Window* m_Window = nullptr;
		frost::core::RenderDevice* m_RenderDevice = nullptr;
		frost::core::SceneManager* m_SceneManager = nullptr;

		frost::core::Scene* m_CurrentScene = nullptr;
		frost::editor::Editor* m_Editor = nullptr;

	public:
		struct InitData
		{
			std::string title;
			glm::ivec2  size;
		};

		// Methods
		virtual void Init() = 0;
		void Init(const InitData& _data);
		virtual void Update(float deltaTime) = 0;
		virtual void Shutdown();
		void Run();

	private:
		void BrowseAllGameObjects(frost::ECS::GameObject* _GameObject, float _DeltaTime);
		void PhysUpdate();

		std::vector<frost::ECS::GameObject*> ObjectsToUpdate;
	};

	/*
	* \brief Macro for creating an application class.
	* \fn int main(int argc, char** argv) FROST_APPLICATION(ApplicationClass)
	* 
	* \details this macro retrieves the class created by the user and inherited from the engine,
	* so that the engine's lifecycle methods can be used on the class passed as the scope of the
	* 'FROST_APPLICATION(ApplicationClass)' macro.
	*/
#define FROST_APPLICATION(ApplicationClass) \
	int main(int argc, char** argv) \
	{ \
		((void)argc); \
		((void)argv); \
		ApplicationClass m_Application; \
		m_Application.Init(); \
		m_Application.Run(); \
		m_Application.Shutdown(); \
		return 0; \
	}
}