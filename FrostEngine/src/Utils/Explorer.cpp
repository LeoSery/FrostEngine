#include "Utils/Explorer.h"
#include "imgui.h"
#include <iostream>

namespace frost::utils
{
	Explorer* Explorer::m_instance = nullptr;

	Explorer::~Explorer()
	{
	}

	Explorer* Explorer::GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new Explorer();
		}

		return m_instance;
	}

	void Explorer::DeleteExplorer()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	void Explorer::DrawExplorer()
	{
		ImGui::SetNextWindowSize(ImVec2(900, 200));
		if (ImGui::Begin("Explorer", NULL, ImGuiWindowFlags_NoCollapse))
		{
			if (ImGui::Button("Back"))
			{
				if (m_currentPath.has_parent_path())
				{
					m_currentPath = m_currentPath.parent_path();
				}
			}
			ImGui::SameLine();
			ImGui::Text("Currenty directoy : %s", m_currentPath.string().c_str());
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
		for (const auto& entry : fs::directory_iterator(m_currentPath))
		{
			const auto is_selected = entry.path() == m_selectedEntry;
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
					m_currentPath /= entry.path().filename();

				m_selectedEntry = entry.path();
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
		for (const auto& entry : fs::directory_iterator(m_currentPath))
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
		if (fs::is_directory(m_selectedEntry))
		{
			ImGui::Text("Selected dir: %s", m_selectedEntry.string().c_str());
		}

		else if (fs::is_regular_file(m_selectedEntry))
		{
			ImGui::Text("Selected file: %s", m_selectedEntry.string().c_str());
		}

		else
		{
			ImGui::Text("Nothing selected!");
		}

		if (fs::is_regular_file(m_selectedEntry) && ImGui::Button("Open"))
		{
			DrawExplorerOpenFile();
		}
		ImGui::SameLine();

		if (ImGui::Button("Rename"))
		{
			m_renameDialogOpened = true;
			ImGui::OpenPopup("Rename File");
		}
		ImGui::SameLine();

		if (ImGui::Button("Delete"))
		{
			m_deleteDialogOpened = true;
			ImGui::OpenPopup("Delete File");
		}

		DrawExplorerRenameFilePopUp();
		DrawExplorerDeleteFilePopUp();
	}

	void Explorer::DrawExplorerRenameFilePopUp()
	{
		if (ImGui::BeginPopupModal("Rename File", &m_renameDialogOpened))
		{
			static char buffer_name[512] = { '\0' };

			ImGui::Text("New name : ");
			ImGui::InputText("###newName", buffer_name, sizeof(buffer_name));

			if (ImGui::Button("Rename"))
			{
				auto new_path = m_selectedEntry.parent_path() / buffer_name;
				if (ExplorerRenameFile(m_selectedEntry, new_path))
				{
					m_renameDialogOpened = false;
					m_selectedEntry = new_path;
					std::memset(buffer_name, 0, sizeof(buffer_name));
				}
			}
			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				m_renameDialogOpened = false;
			}
			ImGui::EndPopup();
		}
	}

	void Explorer::DrawExplorerDeleteFilePopUp()
	{
		if (ImGui::BeginPopupModal("Delete File", &m_deleteDialogOpened))
		{
			ImGui::Text("Are you sure you want to delete %s ?", m_selectedEntry.filename().string().c_str());

			if (ImGui::Button("Yes"))
			{
				if (ExplorerDeleteFile(m_selectedEntry))
				{
					m_selectedEntry.clear();
					m_deleteDialogOpened = false;
				}
			}
			ImGui::SameLine();

			if (ImGui::Button("No"))
			{
				m_deleteDialogOpened = false;
			}
			ImGui::EndPopup();
		}
	}

	void Explorer::DrawExplorerOpenFile()
	{
#ifdef _WIN32
		const auto command = "start \"\" \"" + m_selectedEntry.string() + "\"";

#elif _APPLE_
		const auto command = "open \"" + selectedEntry.string() + "\"";

#else
		const auto command = "xdg-open \"" + selectedEntry.string() + "\"";

#endif    
		std::system(command.c_str());
	}

	bool Explorer::ExplorerRenameFile(const fs::path& _OldPath, const fs::path& _NewPath)
	{
		try
		{
			fs::rename(_OldPath, _NewPath);
			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	bool Explorer::ExplorerDeleteFile(const fs::path& _Path)
	{
		try
		{
			fs::remove(_Path);
			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
		
	}

}