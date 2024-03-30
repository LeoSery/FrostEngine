#include "Utils/TextEditor.h"
#include "imgui.h"

namespace frost::utils
{
	void TextEditor::DrawTextEditor()
	{
		DrawTextEditorMenu();
		DrawTextEditorContent();
		DrawTextEditorInfo();
	}

	void TextEditor::DrawTextEditorMenu()
	{
		if (ImGui::Button("Save"))
		{
			ImGui::OpenPopup("Save File");
		}
		ImGui::SameLine();

		if (ImGui::Button("Load"))
		{
			ImGui::OpenPopup("Load File");
		}
		ImGui::SameLine();


		if (ImGui::Button("Load"))
		{
			ImGui::OpenPopup("Load File");
		}
		ImGui::SameLine();
	}

	void TextEditor::DrawTextEditorContent()
	{
	}

	void TextEditor::DrawTextEditorInfo()
	{
	}

	/*void TextEditor::SaveToFile(std::string_view _Filename)
	{
	}*/

	/*void TextEditor::LoadFromFile(std::string_view _Filename)
	{
	}*/

	/*std::string TextEditor::GetFileExtension(std::string_view _Filename)
	{
		return "";
	}*/
}