#pragma once

/*!
* \file Explorer.h
*
* \brief Header file for the Explorer class.
*/

#include "Core/Internal/Export.h"
#include "Editor/Editor.h"

#include "cstdint"
#include "string_view"
#include "filesystem"
#include "string"

/*!
* \namespace fs std::filesystem
*
* \brief The namespace for the filesystem
*/
namespace fs = std::filesystem;

/*!
* \namespace frost::utils
*
* \brief The namespace for FrostEngine's Utils.
*/
namespace frost::utils
{
	/*!
	* \class Explorer
	*
	* \brief The class has as parent the Editor class which will be apple by him on _DEBUG and _QA Mode.
	*
	* \details This class contains the code logic for the content explorer system Rename/Delete/Filter/Browse/Open file.
	*/
	class FROST_ENGINE_API Explorer : public editor::Editor
	{
	public:

		// Constructors and Destructors

		/*!
		* \brief Constructor for the 'Explorer' class.
		*
		* \details The constructor's initialization list is the user's file path and the item selected in the explorer using lib std::filesystem.
		*
		* \fn Explorer() : m_currentPath(fs::current_path()), m_selectedEntry(fs::path{}) {};
		*
		* \param m_currentPath The user's file path.
		* \param m_selectedEntry The select item in file explorer.
		*
		*/
		Explorer() : m_currentPath(fs::current_path()), m_selectedEntry(fs::path{}) {};

		/*!
		* \brief Destructor for the 'Explorer' class.
		*
		* \details The destructor's call DeleteExplorer().
		*
		* \fn ~Explorer();
		*
		*/
		~Explorer();

		// Singleton

		/*!
		* \brief Singleton for the 'Explorer' class.
		*
		* \details It ensures the existence of a single object 'Explorer' of its kind and provides a single access point to Explorer.
		*
		* \fn [[nodiscard]] static Explorer* GetInstance();
		*
		*/
		[[nodiscard]] static Explorer* GetInstance();

		// Methods Delete Explorer

		/*!
		* \brief Function called at destructor time
		*
		* \details Destroys the instance of our explorer class.
		*
		* \fn static void DeleteExplorer();
		*
		*/
		static void DeleteExplorer();

		// Methods Draw

		/*!
		* \brief Draw Explorer Window.
		*
		* \details Set the explorer's main window and call the other functions.
		*
		* \fn void DrawExplorer();
		*
		*/
		void DrawExplorer();

		/*!
		* \brief Draw Explorer Content.
		*
		* \details Draw the current directory and if we use the back button.
		*
		* \fn void DrawExplorerContent();
		*
		*/
		void DrawExplorerContent();


		/*!
		* \brief Draw Explorer Filtrer.
		*
		* \details Draw the window for the search file extension and the result of it.
		*
		* \fn void DrawExplorerFilter();
		*
		*/
		void DrawExplorerFilter();

		/*!
		* \brief Draw Explorer Actions.
		*
		* \details Draw Text for the folder/file selectioned or when nothing is selected and draw button 'Open' , 'Rename' , 'Delete'.
		*
		* \fn void DrawExplorerActions();
		*
		*/
		void DrawExplorerActions();

		/*!
		* \brief Draw Explorer Rename File PopUp and button 'Rename' and 'Cancel'.
		*
		* \details Rename the file who was selected and PopUp the window For Cancel Or Rename The file.
		*
		* \fn void DrawExplorerRenameFilePopUp();
		*
		*/
		void DrawExplorerRenameFilePopUp();

		/*!
		* \brief Draw Explorer Delete File PopUp with the PopUp Text and button 'Yes' and 'No'.
		*
		* \details Action for Delete the file selected from the folder with an PopUp Window for confirm the action.
		*
		* \fn void DrawExplorerDeleteFilePopUp();
		*
		*/
		void DrawExplorerDeleteFilePopUp();

		/*!
		* \brief Draw Explorer Open File on an Editor.
		*
		* \details Open the file selected depending on the user's operating system (Apple,Window..) .
		*
		* \fn void DrawExplorerOpenFile();
		*
		*/
		void DrawExplorerOpenFile();

		// Methods Open/Close Windows

		/*!
		* \brief Action rename the file selected
		*
		* \details  Action rename the file name corresponding to the variable _OldPath to _NewPath.
		*
		* \fn bool ExplorerRenameFile(const fs::path& _OldPath, const fs::path& _NewPath);
		* 
		* \param _OldPath The selected file path.
		* \param _NewPath The select file path renamed.
		*/
		bool ExplorerRenameFile(const fs::path& _OldPath, const fs::path& _NewPath);

		/*!
		* \brief Action delete the file selected
		*
		* \details  Action delete the file name corresponding to the variable _Path.
		*
		* \fn bool ExplorerDeleteFile(const fs::path& _Path);
		*
		* \param _Path The selected file path.
		* 
		*/
		bool ExplorerDeleteFile(const fs::path& _Path);


	private:

		// Instance
		static Explorer* m_instance;
		frost::ECS::GameObject* m_selectEntity = nullptr;

		// File Path
		fs::path m_currentPath;
		fs::path m_selectedEntry;

		// Boolean
		bool m_renameDialogOpened = false;
		bool m_deleteDialogOpened = false;

	};

}

