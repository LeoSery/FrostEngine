#include "Utils/Logger.h"
#include "imgui.h"
#include <iostream>

namespace frost::utils
{
	Logger* Logger::m_instance = nullptr;

	Logger::Logger()
	{

	}

	Logger::~Logger()
	{

	}

	void Logger::Log(E_LogType _Type, const std::string& _Content)
	{
		m_logStack.push_back({ _Type, _Content });
	}

	void Logger::Show()
	{
#ifndef _RELEASE
		for (const S_LogData& log : m_logStack)
		{
			std::cout << log.logContent << std::endl;
		}
#endif
		m_logStack.clear();
	}

	void Logger::LogInfo(const std::string& _Content)
	{
		GetInstance()->Log(E_LogType::Info, _Content);
	}

	void Logger::LogWarning(const std::string& _Content)
	{
		GetInstance()->Log(E_LogType::Warning, _Content);
	}

	void Logger::LogError(const std::string& _Content)
	{
		GetInstance()->Log(E_LogType::Error, _Content);
	}

	Logger* Logger::GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new Logger();
		}

		return m_instance;
	}

	void Logger::DeleteInstance()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

#ifdef _DEBUG
	void Logger::DrawLogger()
	{

		if (ImGui::Checkbox("Info##Filter", &m_showLogInfo))
		{
		}
		ImGui::SameLine();

		if (ImGui::Checkbox("Warning##Filter", &m_showLogWarning))
		{
		}
		ImGui::SameLine();

		if (ImGui::Checkbox("Error##Filter", &m_showLogError))
		{
		}
		ImGui::SameLine();

		if (ImGui::Button("Clear"))
		{
			m_logStack.clear();
		}

		if (ImGui::BeginTable("Logs##Logger", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
		{
			ImGui::TableSetupColumn("Type");
			ImGui::TableSetupColumn("Message");
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();

			for (const S_LogData& info : m_logStack)
			{
				ImVec4 color = ImVec4(1, 1, 1, 1);
				const char* text = nullptr;
				switch (info.logType)
				{
				case E_LogType::Info:
				{
					if (!m_showLogInfo)
					{
						continue;
					}

					color = ImVec4(1, 1, 1, 1);
					text = "Info";
				}
				break;

				case E_LogType::Warning:
				{
					if (!m_showLogWarning)
					{
						continue;
					}

					color = ImVec4(1, 1, 0, 1);
					text = "Warning";
				}
				break;

				case E_LogType::Error:
				{
					if (!m_showLogError)
					{
						continue;
					}

					color = ImVec4(1, 0, 0, 1);
					text = "Error";
				}
				break;

				default:
					continue;
				}

				ImGui::TableSetColumnIndex(0);
				ImGui::TextColored(color, text);
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(info.logContent.c_str());
				ImGui::TableNextRow();
			}

			ImGui::EndTable();
		}
	}
#endif
}
