#pragma once

/*!
* \file Editor.h
* 
* \brief Header file for the Editor class.
*/

#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/Internal/Export.h"

#include "cstdint"
#include "string_view"
#include "filesystem"
#include "string"


namespace frost::core {
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
	class Explorer;
}
#pragma endregion
namespace fs = std::filesystem;

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
		Editor() : CurrentPath(fs::current_path()), selectedEntry(fs::path{}){};
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
		
		void DrawExplorerContent();
		void DrawExplorerFilter();
		void DrawExplorerActions();
		void DrawExplorerRenameFilePopUp();
		void DrawExplorerDeleteFilePopUp();
		void DrawExplorerOpenFile();

	
		
		//example collide
		bool ISCollide = true;
		bool ShowInspector = false;
		bool ExplorerRenameFile(const fs::path& old_path, const fs::path& new_path);
		bool ExplorerDeleteFile(const fs::path& path);
		bool RenameDialogOpened = false;
		bool DeleteDialogOpened = false;
	private:

		static Editor* m_Instance;
		frost::ECS::GameObject* SelectEntity = nullptr;
		
		fs::path CurrentPath;
		fs::path selectedEntry;
	};
}
