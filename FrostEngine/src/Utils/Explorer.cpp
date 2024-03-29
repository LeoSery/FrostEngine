#include "Utils/Explorer.h"
#include "imgui.h"

namespace frost::utils
{
	Explorer::Explorer()
	{
	}
	Explorer::~Explorer()
	{
	}

	void Explorer::DrawExplorer()
	{
		DrawMenu();
		ImGui::Separator();
		DrawContent();
		ImGui::Separator();
		DrawActions();
		ImGui::Separator();
		DrawFilter();
	}

	void Explorer::DrawMenu()
	{

	}

	void Explorer::DrawContent()
	{
	}

	void Explorer::DrawActions()
	{
	}

	void Explorer::DrawFilter()
	{
	}

	/*Explorer* Explorer::GetInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new Explorer();
		}

		return m_Instance;
	}*/

	/*void Explorer::DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}*/




}