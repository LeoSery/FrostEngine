#pragma once

/*!
* \file TextEditor.h
*
* \brief Header file for the TextEditor class.
*/

#include "Core/Internal/Export.h"
#include "Editor/Editor.h"

#include "cstdint"
#include "cstring"

#include "string_view"
#include "string"

#include "imgui.h"
#include "filesystem"

#include "fstream"
#include "iostream"
#include "sstream"

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
	* \class TextEditor
	*
	* \brief The class has as parent the Editor class which will be apple by him on _DEBUG Mode.
	*
	* \details This class contains the code logic for the content text editor system Save/Load/Clear/Edit file.
	*/
	class FROST_ENGINE_API TextEditor : public editor::Editor
	{
	public:

		// Constructors and Destructors

		/*!
		* \brief Constructor for the 'TextEditor' class.
		*
		* \details The constructor's initialization list is the current filename has an empty string,
		* we use the memset function to set text buffer and buffer size.
		* \fn TextEditor() : m_currentFilename({}) { std::memset(m_textBuffer, 0, m_bufferSize); }
		*
		*/
		TextEditor() : m_currentFilename({}) { std::memset(m_textBuffer, 0, m_bufferSize); }

		/*!
		* \brief Destructor for the 'TextEditor' class.
		*
		* \details The destructor's call DeleteTextEditor().
		*
		* \fn ~TextEditor();
		*
		*/
		~TextEditor();

		// Singleton

		/*!
		* \brief Singleton for the 'TextEditor' class.
		*
		* \details It ensures the existence of a single object 'TextEditor' of its kind and provides a single access point to TextEditor.
		*
		* \fn [[nodiscard]] static TextEditor* GetInstance();
		*
		*/
		[[nodiscard]] static TextEditor* GetInstance();

		/*!
		* \brief Function called at destructor time.
		*
		* \details Destroys the instance of our text editor class.
		*
		* \fn static void DeleteEditor();
		*
		*/
		static void DeleteTextEditor();

		// Methods Draw

		/*!
		* \brief Draw Text Editor.
		*
		* \details Call the Menu/Content/Info function.
		*
		* \fn void DrawTextEditor();
		*
		*/
		void DrawTextEditor();

		/*!
		* \brief Set button and control.
		*
		* \details Set ImGui key control and action popup if we clicked on button Save/Load/Clear.
		* 
		* \fn void DrawTextEditorMenu();
		*
		*/
		void DrawTextEditorMenu();

		/*!
		* \brief Set text variable.
		*
		* \details Set text variable for the number of lines in the file and its contents
		*
		* \fn void DrawTextEditorContent();
		*
		*/
		void DrawTextEditorContent();

		/*!
		* \brief Information display.
		*
		* \details Displays information about the opent file and are extension
		*
		* \fn void DrawTextEditorInfo();
		*
		*/
		void DrawTextEditorInfo();

		// Methods Draw PopUp

		/*!
		* \brief SavePopup.
		*
		* \details This function contains the code logic for the save file and his filename Popup. 
		*
		* \fn void DrawTextEditorSavePopup();
		*
		*/
		void DrawTextEditorSavePopup();

		/*!
		* \brief LoadPopup.
		*
		* \details This function contains the code logic for the load file and his filename Popup.
		*
		* \fn void DrawTextEditorLoadPopup();
		*
		*/
		void DrawTextEditorLoadPopup();

		// Text Variable
		static constexpr auto m_bufferSize = std::size_t{ 1024 };


		// PopUp Variable
		static constexpr auto m_popUpFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
		static constexpr auto m_popUpSize = ImVec2(300.0f, 100.0f);
		static constexpr auto m_popUpButtonSize = ImVec2(120.0f, 0.0f);

	private:

		// Methods Act On Files
		void SaveToFile(std::string_view _Filename);
		void LoadFromFile(std::string_view _Filename);
		std::string GetFileExtension(std::string_view _Filename);

		// Variable Text
		char m_textBuffer[m_bufferSize];
		std::string m_currentFilename;

		// Instance
		static TextEditor* m_instance;


	};
}

