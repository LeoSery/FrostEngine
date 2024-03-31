#include "Utils/TextEditor.h"


namespace frost::utils
{
	TextEditor* TextEditor::m_Instance = nullptr;

	TextEditor::~TextEditor()
	{
	}

	TextEditor* TextEditor::GetInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new TextEditor();
		}

		return m_Instance;
	}

	void TextEditor::DeleteTextEditor()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

	void TextEditor::DrawTextEditor()
	{
		DrawTextEditorMenu();
		DrawTextEditorContent();
		DrawTextEditorInfo();
	}

	void TextEditor::DrawTextEditorMenu()
	{
		const auto ctrl_pressed = ImGui::GetIO().KeyCtrl;
		//const auto esc_pressed = ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape));
		const auto s_pressed = ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape));
		const auto l_pressed = ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape));

		if (ImGui::Button("Save") || (ctrl_pressed && s_pressed))
		{
			ImGui::OpenPopup("Save File");
		}
		ImGui::SameLine();

		if (ImGui::Button("Load") || (ctrl_pressed && l_pressed))
		{
			ImGui::OpenPopup("Load File");
		}
		ImGui::SameLine();


		if (ImGui::Button("Clear"))
		{
			std::memset(TextBuffer, 0, BufferSize);
		}

		DrawTextEditorSavePopup();
		DrawTextEditorLoadPopup();
	}

	void TextEditor::DrawTextEditorContent()
	{
		static constexpr auto inputTextSize = ImVec2(1200.0f, 625.0f);
		static constexpr auto lineNumberSize = ImVec2(30.0f, inputTextSize.y);
		static constexpr auto inputTextFlags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_NoHorizontalScroll;

		ImGui::BeginChild("LineNumbers", lineNumberSize);
		const auto line_count = std::count(TextBuffer, TextBuffer + BufferSize, '\n') + 1;
		for (auto i = 1; i <= line_count; ++i)
		{
			ImGui::Text("%d", i);
		}
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::InputTextMultiline("###inputField", TextBuffer, BufferSize, inputTextSize, inputTextFlags);
	}

	void TextEditor::DrawTextEditorInfo()
	{
		if (CurrentFilename.size() == 0)
		{
			ImGui::Text("No File Opened!");
			return;
		}

		const auto file_extension = GetFileExtension(CurrentFilename);
		ImGui::Text("Opened file %s | File extension %s", CurrentFilename.data(), file_extension.data());
	}

	void TextEditor::DrawTextEditorSavePopup()
	{
		static char saveFilenameBuffer[256] = "text.txt";
		const auto esc_pressed = ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape));
		
		ImGui::SetNextWindowSize(popUpSize);
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2.0f - popUpSize.x / 2.0f, ImGui::GetIO().DisplaySize.x / 20.f - popUpSize.y / 2.0f));

		if (ImGui::BeginPopupModal("Save File", nullptr, popUpFlags))
		{
			ImGui::InputText("Filename", saveFilenameBuffer, sizeof(saveFilenameBuffer));
			if (ImGui::Button("Save", popUpButtonSize))
			{
				SaveToFile(saveFilenameBuffer);
				CurrentFilename = saveFilenameBuffer;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();

			if (ImGui::Button("Cancel", popUpButtonSize) || esc_pressed)
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	void TextEditor::DrawTextEditorLoadPopup()
	{
		static char loadFilenameBuffer[256] = "text.txt";
		const auto esc_pressed = ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape));

		ImGui::SetNextWindowSize(popUpSize);
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2.0f - popUpSize.x / 2.0f, ImGui::GetIO().DisplaySize.x / 20.f - popUpSize.y / 2.0f));

		if (ImGui::BeginPopupModal("Load File"))
		{
			ImGui::InputText("Filename", loadFilenameBuffer, sizeof(loadFilenameBuffer));
			if (ImGui::Button("Load", popUpButtonSize))
			{
				LoadFromFile(loadFilenameBuffer);
				CurrentFilename = loadFilenameBuffer;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();

			if (ImGui::Button("Cancel") || esc_pressed)
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	void TextEditor::SaveToFile(std::string_view _Filename)
	{
		auto out = std::ofstream{ _Filename.data() };

		if (out.is_open())
		{
			out << TextBuffer;
			out.close();
		}
	}

	void TextEditor::LoadFromFile(std::string_view _Filename)
	{
		auto in = std::ifstream{ _Filename.data()};

		if (in.is_open())
		{
			auto buffer = std::stringstream{};
			buffer << in.rdbuf();
			std::memcpy(TextBuffer, buffer.str().data(), BufferSize);
			in.close();
		}
	}

	std::string TextEditor::GetFileExtension(std::string_view _Filename)
	{
		const auto file_path = fs::path{ _Filename };
		return file_path.extension().string();
	}
}