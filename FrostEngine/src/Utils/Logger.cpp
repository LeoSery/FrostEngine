#include "Utils/Logger.h"

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
}
