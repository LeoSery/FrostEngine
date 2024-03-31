#pragma once

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

namespace fs = std::filesystem;

namespace frost::utils
{
	class FROST_ENGINE_API TextEditor : public editor::Editor
	{
	public:

		// Constructors and Destructors
		TextEditor() : CurrentFilename({}) { std::memset(TextBuffer, 0, BufferSize); }
		~TextEditor();

		// Singleton
		[[nodiscard]] static TextEditor* GetInstance();
		static void DeleteTextEditor();

		// Methods Draw
		void DrawTextEditor();
		void DrawTextEditorMenu();
		void DrawTextEditorContent();
		void DrawTextEditorInfo();

		// Methods Draw PopUp
		void DrawTextEditorSavePopup();
		void DrawTextEditorLoadPopup();

		// Text Variable
		static constexpr auto BufferSize = std::size_t{ 1024 };


		// PopUp Variable
		static constexpr auto popUpFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
		static constexpr auto popUpSize = ImVec2(300.0f, 100.0f);
		static constexpr auto popUpButtonSize = ImVec2(120.0f, 0.0f);

	private:

		// Methods Act On Files
		void SaveToFile(std::string_view _Filename);
		void LoadFromFile(std::string_view _Filename);
		std::string GetFileExtension(std::string_view _Filename);

		// Variable Text
		char TextBuffer[BufferSize];
		std::string CurrentFilename;

		// Instance
		static TextEditor* m_Instance;


	};
}

