#pragma once

#include "Core/Internal/Export.h"
#include "Editor/Editor.h"

#include "cstdint"
#include "string_view"

namespace frost::utils
{
	class FROST_ENGINE_API TextEditor : public editor::Editor
	{
	public:

		// Constructors and Destructors
		TextEditor() : CurrentFilename({}) { std::memset(TextBuffer, 0, BufferSize); }

		// Methods Darw
		void DrawTextEditor();
		void DrawTextEditorMenu();
		void DrawTextEditorContent();
		void DrawTextEditorInfo();

		// Variable Text
		static constexpr auto BufferSize = std::size_t{ 1024 };

	private:

		// Methods act on files
		// void SaveToFile(std::string_view _Filename);
		// void LoadFromFile(std::string_view _Filename);
		// std::string GetFileExtension(std::string_view _Filename);

		// Variable Text
		char TextBuffer[BufferSize];
		std::string CurrentFilename;
	};
}

