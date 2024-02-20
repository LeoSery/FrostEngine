#include "Utils/Logger.h"

#include <iostream>

namespace frost::utils
{
	Logger* Logger::m_Instance = nullptr;

	Logger::Logger()
	{

	}

	Logger::~Logger()
	{

	}

	void Logger::Log(LogType _Type, const std::string& _Content)
	{
		m_LogStack.push_back({ _Type, _Content });
	}

	void Logger::Show()
	{
		for (const LogData& log : m_LogStack)
		{
			std::cout << log.LogContent << std::endl;
		}
	}

	void Logger::LogInfo(const std::string& _Content)
	{
		GetInstance()->Log(LogType::Info, _Content);
	}

	void Logger::LogWarning(const std::string& _Content)
	{
		GetInstance()->Log(LogType::Warning, _Content);
	}

	void Logger::LogError(const std::string& _Content)
	{
		GetInstance()->Log(LogType::Error, _Content);
	}

	Logger* Logger::GetInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new Logger();
		}

		return m_Instance;
	}

	void Logger::DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
}
