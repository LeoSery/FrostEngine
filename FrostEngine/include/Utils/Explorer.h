#pragma once

#include "Core/Internal/Export.h"
#include "Editor/Editor.h"

#include "cstdint"
#include "string_view"
#include "filesystem"
#include "string"


namespace fs = std::filesystem;

namespace frost::utils
{
	
	
	class FROST_ENGINE_API Explorer : public editor::Editor
	{
	public:

		//Constructors and Destructors
		Explorer() : CurrentPath(fs::current_path()), selectedEntry(fs::path{}) {};
		~Explorer();

		// Singleton
		[[nodiscard]] static Explorer* GetInstance();
		static void DeleteExplorer();

		//Methods
		void DrawExplorer();
		void DrawExplorerContent();
		void DrawExplorerFilter();
		void DrawExplorerActions();
		void DrawExplorerRenameFilePopUp();
		void DrawExplorerDeleteFilePopUp();
		void DrawExplorerOpenFile();




		bool ExplorerRenameFile(const fs::path& old_path, const fs::path& new_path);
		bool ExplorerDeleteFile(const fs::path& _path);
		bool RenameDialogOpened = false;
		bool DeleteDialogOpened = false;

	private:
		static Explorer* m_Instance;
		frost::ECS::GameObject* SelectEntity = nullptr;

		fs::path CurrentPath;
		fs::path selectedEntry;




	};

}

