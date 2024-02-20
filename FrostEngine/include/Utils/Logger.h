#pragma once

#include <vector>
#include <string>

namespace frost::utils
{
	enum class LogType
	{
		Info,
		Warning,
		Error
	};

	class Logger
	{
	public:

		//Constructors and Destructors
		Logger();
		~Logger();

		//Methods
		void Log(LogType _Type, const std::string& _Content);
		void Show();

		//Static Methods
		static void LogInfo(const std::string& _Content);
		static void LogWarning(const std::string& _Content);
		static void LogError(const std::string& _Content);

		// Singleton
		static Logger* GetInstance();
		static void DeleteInstance();

	private:
		struct LogData
		{
			LogType LogType;
			std::string LogContent;
		};

		static Logger* m_Instance;
		std::vector<LogData> m_LogStack;
		bool m_ShowLogError = true;
		bool m_ShowLogWarning = true;
		bool m_ShowLogInfo = true;
	};
}
