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

#include "Core/Internal//Window.h"
#include "Core/Internal/Export.h"

#include "Render/RenderDevice.h"
#include "Render/RenderDevice.h"

#include "Editor/Editor.h"

#include "Utils/Logger.h"

#include <chrono>
#include <thread>

/*!
 * \namespace frost
 *
 * \brief The main namespace for the FrostEngine.
 *
 * \details frost is the engine's main namespace and contains the engine's
 * update loop for updating GameObjects, physics and OpenGL rendering.
 */
namespace frost
{
	/*!
	* \class Application
	* \brief Main engine class that initializes/shuts down the different engine modules,
	* runs the main loop for updating physics, GameObjects and rendering,
	* and all the components on which they depend.
	*/
	class FROST_ENGINE_API Application
	{
	protected:

		frost::core::Window* m_Window = nullptr;
		frost::render::RenderDevice* m_RenderDevice = nullptr;
		frost::core::SceneManager* m_SceneManager = nullptr;
		frost::core::Scene* m_CurrentScene = nullptr;
		frost::editor::Editor* m_Editor = nullptr;

	public:

		//
		// Structs
		//

		/*!
		* \struct InitData
		*
		* \brief A struct that holds data for initializing the window.
		*
		* \details This structure contains the title and size of the window to be created.
		*/
		struct S_InitData
		{
			std::string title;
			glm::ivec2  size;
		};

		//
		// Methods
		//

		/*!
		* \brief Engine initialization method
		* 
		* \details Method call by the user to initialize the engine and its different modules.
		* This method is purely virtual and must be redefined on the game side by the user in
		* the class he inherits from the engine. 
		* 
		* \fn void Application::Init()
		*/
		virtual void Init() = 0;

		/*!
		* \brief Internal method for initializing the engine and its different modules.
		*
		* \fn void Application::Init(const InitData& _data)
		*
		* \param _data Initialization data containing window title and size.
		*/
		void Init(const S_InitData& _data);

		/*!
		* \brief Engine update method.
		* 
		* \details Method called by the user to execute code at each frame.
		* This method is purely virtual and must be redefined on the game
		* side by the user in the class he inherits from the engine. 
		* 
		* \fn void Application::Update(float deltaTime)
		* 
		* \param deltaTime The time between two frames.
		*/
		virtual void Update(float deltaTime) = 0;

		/*!
		* \brief Engine shutdown method.
		*
		* \details Shutdown is called when the engine is closed, deletes all processes opened by the engine.
		* 
		* \fn void Application::Shutdown()
		*/
		virtual void Shutdown();

		/*!
		* \brief Engine main loop method.
		* 
		* \details Infinite engine loop that runs as long as the engine is open,
		* updating the engine state at each frame. It renders in the following order:
		* Update user > Update GameObjects > Update Components > Update physics > Update inputs > Update render > Update logger.
		*
		* \fn void Application::Run()
		*/
		void Run();

		void UpdateDebugData(float* _DeltaTime);

	private:

		/*!
		* \brief Browse all GameObjects in the current scene.
		*
		* \details Go through the Tree of GameObjects of the currently active scene,
		* add each object to the rendering queue, call its 'Update()' method and recursively
		* do the same with each of its children.
		* 
		* \fn void Application::BrowseAllGameObjects(frost::ECS::GameObject* _GameObject, float _DeltaTime)
		*
		* \param _GameObject The game object to update.
		* \param _DeltaTime The time between the last frame and the current frame.
		*/
		void BrowseAllGameObjects(frost::ECS::GameObject* _GameObject, float _DeltaTime);

		/*!
		* \brief Computes and applies collisions for each GameObject in the rendering list.
		*
		* \details Performs the physical rendering of the engine. For each GameObject in the renderer,
		* retrieves its BoxCollider component, and checks whether it collides with all other objects in the scene.
		* 
		* \fn void Application::PhysUpdate()
		*
		* If it does, this object is added to the 'Hits' map, with a 'CollisionData' vector for each object with which it collides.
		* Then, for each Hit of each GameObject, we call its 'OnCollisionEnter()' method, passing it 'CollisionData' as a parameter.
		*
		* Finally, we move the object with the corresponding collision data.
		*/
		void PhysUpdate();

		std::vector<frost::ECS::GameObject*> ObjectsToUpdate;


	};

	/*!
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
