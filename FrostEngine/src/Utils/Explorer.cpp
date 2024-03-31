#include "Utils/Explorer.h"
#include "imgui.h"
#include <iostream>

namespace frost::utils
{
	Explorer* Explorer::m_Instance = nullptr;

	Explorer::~Explorer()
	{
	}

	Explorer* Explorer::GetInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new Explorer();
		}

		return m_Instance;
	}

	void Explorer::DeleteExplorer()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

	void Explorer::DrawExplorer()
	{
		ImGui::SetNextWindowSize(ImVec2(900, 200));
		if (ImGui::Begin("Explorer", NULL, ImGuiWindowFlags_NoCollapse))
		{
			if (ImGui::Button("Back"))
			{
				if (CurrentPath.has_parent_path())
				{
					CurrentPath = CurrentPath.parent_path();
				}
			}
			ImGui::SameLine();
			ImGui::Text("Currenty directoy : %s", CurrentPath.string().c_str());
			ImGui::Separator();
			DrawExplorerContent();
			ImGui::Separator();
			DrawExplorerActions();
			ImGui::Separator();
			DrawExplorerFilter();


			ImGui::End();
		}
	}

	void Explorer::DrawExplorerContent()
	{
		for (const auto& entry : fs::directory_iterator(CurrentPath))
		{
			const auto is_selected = entry.path() == selectedEntry;
			const auto is_directory = entry.is_directory();
			const auto is_file = entry.is_regular_file();
			auto entry_name = entry.path().filename().string();

			if (is_directory)
				entry_name = "[Directory]" + entry_name;
			else if (is_file)
				entry_name = "[File]" + entry_name;

			if (ImGui::Selectable(entry_name.c_str(), is_selected))
			{
				if (is_directory)
					CurrentPath /= entry.path().filename();

				selectedEntry = entry.path();
			}
		}
	}

	void Explorer::DrawExplorerFilter()
	{
		static char extension_filter[16] = { "\0" };

		ImGui::Text("Filter by extension");
		ImGui::SameLine();
		ImGui::InputText("###inFilter", extension_filter, sizeof(extension_filter));

		if (std::strlen(extension_filter) == 0)
			return;

		auto filtered_file_count = std::size_t{ 0 };
		for (const auto& entry : fs::directory_iterator(CurrentPath))
		{
			if (!fs::is_regular_file(entry))
				continue;

			if (entry.path().extension().string() == extension_filter)
				++filtered_file_count;
		}

		ImGui::Text("Number of files: %u", filtered_file_count);
	}

	void Explorer::DrawExplorerActions()
	{
		if (fs::is_directory(selectedEntry))
		{
			ImGui::Text("Selected dir: %s", selectedEntry.string().c_str());
		}

		else if (fs::is_regular_file(selectedEntry))
		{
			ImGui::Text("Selected file: %s", selectedEntry.string().c_str());
		}

		else
		{
			ImGui::Text("Nothing selected!");
		}

		if (fs::is_regular_file(selectedEntry) && ImGui::Button("Open"))
		{
			DrawExplorerOpenFile();
		}
		ImGui::SameLine();

		if (ImGui::Button("Rename"))
		{
			RenameDialogOpened = true;
			ImGui::OpenPopup("Rename File");
		}
		ImGui::SameLine();

		if (ImGui::Button("Delete"))
		{
			DeleteDialogOpened = true;
			ImGui::OpenPopup("Delete File");
		}

		DrawExplorerRenameFilePopUp();
		DrawExplorerDeleteFilePopUp();
	}

	void Explorer::DrawExplorerRenameFilePopUp()
	{
		if (ImGui::BeginPopupModal("Rename File", &RenameDialogOpened))
		{
			static char buffer_name[512] = { '\0' };

			ImGui::Text("New name : ");
			ImGui::InputText("###newName", buffer_name, sizeof(buffer_name));

			if (ImGui::Button("Rename"))
			{
				auto new_path = selectedEntry.parent_path() / buffer_name;
				if (ExplorerRenameFile(selectedEntry, new_path))
				{
					RenameDialogOpened = false;
					selectedEntry = new_path;
					std::memset(buffer_name, 0, sizeof(buffer_name));
				}
			}
			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				RenameDialogOpened = false;
			}
			ImGui::EndPopup();
		}
	}

	void Explorer::DrawExplorerDeleteFilePopUp()
	{
		if (ImGui::BeginPopupModal("Delete File", &DeleteDialogOpened))
		{
			ImGui::Text("Are you sure you want to delete %s ?", selectedEntry.filename().string().c_str());

			if (ImGui::Button("Yes"))
			{
				if (ExplorerDeleteFile(selectedEntry))
				{
					selectedEntry.clear();
					DeleteDialogOpened = false;
				}
			}
			ImGui::SameLine();

			if (ImGui::Button("No"))
			{
				DeleteDialogOpened = false;
			}
			ImGui::EndPopup();
		}
	}

	void Explorer::DrawExplorerOpenFile()
	{
#ifdef _WIN32
		const auto command = "start \"\" \"" + selectedEntry.string() + "\"";

#elif _APPLE_
		const auto command = "open \"" + selectedEntry.string() + "\"";

#else
		const auto command = "xdg-open \"" + selectedEntry.string() + "\"";

#endif    
		std::system(command.c_str());
	}

	bool Explorer::ExplorerRenameFile(const fs::path& old_path, const fs::path& new_path)
	{
		try
		{
			fs::rename(old_path, new_path);
			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	bool Explorer::ExplorerDeleteFile(const fs::path& _path)
	{
		try
		{
			fs::remove(_path);
			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
		
	}

}