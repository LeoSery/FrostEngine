#pragma once

/*!
* \file Editor.h
* 
* \brief Header file for the Editor class.
*/

#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/Internal/Export.h"

#pragma region Forward Declarations

namespace frost::core
{
	class Window;
	class Scene;
	class SceneManager;	
}

namespace frost::ECS
{
	class GameObject;
}

namespace frost::utils
{
	class Logger;
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
	* the FrostEngine runtime editor, such as the 'Hierarchy', 'Inspector'
	* and 'Console'.
	*/
	class FROST_ENGINE_API Editor
	{
	public:

		// Constructor & Destructor
		Editor();
		~Editor();

		// Singleton
		[[nodiscard]] static Editor* GetInstance();
		static void DeleteEditor();

		// Methods
		int DrawEditor();
		int Init(const frost::core::Window* _Window);
		void Shutdown();

		void DrawHierachyValue(frost::core::Scene* m_CurrentScene);
		void DrawInsperctorValue();
		
		// Data
		bool ISCollide = true;
		bool ShowInspector = false;

	private:

		static Editor* m_Instance;
		frost::ECS::GameObject* SelectEntity = nullptr;
	};
}
