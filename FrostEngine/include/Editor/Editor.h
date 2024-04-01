#pragma once

/*!
* \file Editor.h
* 
* \brief Header file for the Editor class.
*/

#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"

#include "Core/Internal/Export.h"


/*!
* \namespace frost::core
*
* \brief The namespace for the Window/Scene/SceneManager class.
*/
namespace frost::core {
	class Window;
	class Scene;
	class SceneManager;
}

/*!
* \namespace frost::ECS
*
* \brief The namespace for the GameObject class.
*/
namespace frost::ECS
{
	class GameObject;
}

/*!
* \namespace frost::utils
*
* \brief The namespace for the Logger/Explorer/TextEditor class.
*/
namespace frost::utils
{
	class Logger;
	class Explorer;
	class TextEditor;
}

/*!
* \namespace frost
*
* \brief The namespace for the Application class.
*/
namespace frost
{
	class Application;
}

#pragma endregion


/*!
* \namespace frost::editor
*
* \brief The namespace for FrostEngine's Editor.
*/
namespace frost::editor
{
	/*!
	* \class Editor
	* 
	* \brief  The 'Editor' class manages all the engine's editing functions.
	* 
	* \details  The 'Editor' class will display the different windows of
	* the FrostEngine runtime editor, such as the 'Hierarchy', 'Inspector' ,'FPS'
	* and 'Console'.
	*/
	class FROST_ENGINE_API Editor
	{
	public:

		// Constructor Destructor 

		/*!
		* \brief Constructor for the 'Editor' class.
		*
		* \fn Editor();
		*
		*/
		Editor();

		/*!
		* \brief Destructor for the 'Editor' class.
		*
		* \details Call the DeleteEditor function.
		* 
		* \fn ~Editor();
		*
		*/
		~Editor();

		// Singleton 

		/*!
		* \brief Singleton for the 'Editor' class.
		*
		* \details It ensures the existence of a single object 'Editor' of its kind and provides a single access point to Editor.
		*
		* \fn [[nodiscard]] static Editor* GetInstance();
		*
		*/
		[[nodiscard]] static Editor* GetInstance();

		// Methods Delete Editor

		/*!
		* \brief Function called at destructor time.
		*
		* \details Destroys the instance of our editor class.
		*
		* \fn static void DeleteEditor();
		*
		*/
		static void DeleteEditor();

		//Methods 

		/*!
		* \brief Draw Editor Window and the other Windows.
		*
		* \details Instantiate Scene/SceneManager to be able to draw on the present scene.
		* Implements Glw/Opengl3 Frame and set the editor's main window and call the other functions draw window,
		* for the Inspector/FPS/Explorer/Console depending on whether you are in _DEBUG/_QA/_RELEASE Mode.
		*
		* \fn int DrawEditor();
		*
		*/
		int DrawEditor();

		/*!
		* \brief Is introducing the use of Opengl3/ImGui/Glfw.
		*
		* \details Initialization of ImGui with Opengl3 and Glfw.
		*
		* \fn int Init(const frost::core::Window* _Window);
		*
		*/
		int Init(const frost::core::Window* _Window);

		/*!
		* \brief Shutdown Opengl3/ImGui/Glfw.
		*
		* \details Shutdown ImGui/Opengl3 and ImGui.
		*
		* \fn void Shutdown();
		*
		*/
		void Shutdown();

		/*!
		* \brief Return Methods for GameObject variable.
		*
		* \details Return the SelectedEntity who has for variable type frost::ECS::GameObject.
		*
		* \fn frost::ECS::GameObject* GetSelectEntity();
		*
		*/
		frost::ECS::GameObject* GetSelectEntity();

		/*!
		* \brief Assigns a value to the variable SelectEntity.
		*
		* \details The variable SelectEntity takes the value of the _Entity parameter.
		*
		* \fn void SetSelectEntity(frost::ECS::GameObject* _Entity);
		*
		* \param  _Entity is an frost::ECS::GameObject type which represents the selected object.
		* 
		*/
		void SetSelectEntity(frost::ECS::GameObject* _Entity);

		// Draw windows

		/*!
		* \brief Draw Hirerarchy Window.
		*
		* \details Set the Hierarchy Window and call the DrawHierachyValue/DrawInspectorValue function.
		*
		* \fn void DrawHierarchy(frost::core::Scene* _CurrentScene);
		*
		* \param  _CurrentScene is frost::core::Scene type which represents the game scene.
		*
		*/
		void DrawHierarchy(frost::core::Scene* _CurrentScene);

		/*!
		* \brief Draw The GameObject on the Hirerarchy Window.
		*
		* \details Loop on all game objects on the scene and assign them a button that if clicked take the value selectentity.
		*
		* \fn void DrawHierachyValue(frost::core::Scene* _CurrentScene);
		*
		* \param _CurrentScene is frost::core::Scene type which represents the game scene.
		*
		*/
		void DrawHierachyValue(frost::core::Scene* _CurrentScene);

		/*!
		* \brief Draw Inspector Window.
		*
		* \details Set the Inspector Window.
		*
		* \fn void DrawInspector();
		*
		*/
		void DrawInspector();

		/*!
		* \brief Draw The InspectorValue on the Window.
		*
		* \details If we select an Entity on the hierarchy (through the variable SelectEntity),
		* we recover are Transform/BoxCollider/SpriteRender and we can change these values.
		*
		* \fn void DrawInsperctorValue();
		*
		*/
		void DrawInsperctorValue();

		/*!
		* \brief Draw FPS Window
		*
		* \details Set the Fps Window and draw the (FpsString) variable inside.
		* 
		* \fn void DrawFps();
		*
		*/
		void DrawFps();
#if defined _DEBUG || _QA
		
		/*!
		* \brief Draw Console Window
		*
		* \details Set the Console Window and call DrawLogger() function in.
		*
		* \fn void DrawConsole();
		*
		*/
		void DrawConsole();
#endif	

		// Fps Variable
		float m_fps = 0.0;
		float m_secondCounter = 0.0;
		float m_tempFps = 0.0;
		
	private:

		// Instance
		static Editor* m_instance;
		frost::ECS::GameObject* m_selectEntity = nullptr;
	};
}
