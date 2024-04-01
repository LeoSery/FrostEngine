#include "Utils/TextEditor.h"


namespace frost::utils
{
	TextEditor* TextEditor::m_instance = nullptr;

	TextEditor::~TextEditor()
	{
		//DeleteTextEditor();
	}

	TextEditor* TextEditor::GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new TextEditor();
		}

		return m_instance;
	}

	void TextEditor::DeleteTextEditor()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;*

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
			std::memset(m_textBuffer, 0, m_bufferSize);
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
		const auto line_count = std::count(m_textBuffer, m_textBuffer + m_bufferSize, '\n') + 1;
		for (auto i = 1; i <= line_count; ++i)
		{
			ImGui::Text("%d", i);
		}
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::InputTextMultiline("###inputField", m_textBuffer, m_bufferSize, inputTextSize, inputTextFlags);
	}

	void TextEditor::DrawTextEditorInfo()
	{
		if (m_currentFilename.size() == 0)
		{
			ImGui::Text("No File Opened!");
			return;
		}

		const auto file_extension = GetFileExtension(m_currentFilename);
		ImGui::Text("Opened file %s | File extension %s", m_currentFilename.data(), file_extension.data());
	}

	void TextEditor::DrawTextEditorSavePopup()
	{
		static char saveFilenameBuffer[256] = "text.txt";
		const auto esc_pressed = ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape));
		
		ImGui::SetNextWindowSize(m_popUpSize);
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2.0f - m_popUpSize.x / 2.0f, ImGui::GetIO().DisplaySize.x / 20.f - m_popUpSize.y / 2.0f));

		if (ImGui::BeginPopupModal("Save File", nullptr, m_popUpFlags))
		{
			ImGui::InputText("Filename", saveFilenameBuffer, sizeof(saveFilenameBuffer));
			if (ImGui::Button("Save", m_popUpButtonSize))
			{
				SaveToFile(saveFilenameBuffer);
				m_currentFilename = saveFilenameBuffer;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();

			if (ImGui::Button("Cancel", m_popUpButtonSize) || esc_pressed)
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

		ImGui::SetNextWindowSize(m_popUpSize);
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2.0f - m_popUpSize.x / 2.0f, ImGui::GetIO().DisplaySize.x / 20.f - m_popUpSize.y / 2.0f));

		if (ImGui::BeginPopupModal("Load File"))
		{
			ImGui::InputText("Filename", loadFilenameBuffer, sizeof(loadFilenameBuffer));
			if (ImGui::Button("Load", m_popUpButtonSize))
			{
				LoadFromFile(loadFilenameBuffer);
				m_currentFilename = loadFilenameBuffer;
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
			out << m_textBuffer;
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
			std::memcpy(m_textBuffer, buffer.str().data(), m_bufferSize);
			in.close();
		}
	}

	std::string TextEditor::GetFileExtension(std::string_view _Filename)
	{
		const auto file_path = fs::path{ _Filename };
		return file_path.extension().string();
	}
}