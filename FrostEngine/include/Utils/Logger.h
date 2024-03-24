#pragma once

#include "Core/Export.h"

#include <vector>
#include <string>

namespace frost::utils
{
	enum class E_LogType
	{
		Info,
		Warning,
		Error
	};

	class FROST_ENGINE_API Logger
	{
	public:

		//Constructors and Destructors
		Logger();
		~Logger();

		//Methods
		void Log(E_LogType _Type, const std::string& _Content);
		void Show();

		//Static Methods
		static void LogInfo(const std::string& _Content);
		static void LogWarning(const std::string& _Content);
		static void LogError(const std::string& _Content);

#ifdef _DEBUG
		void DrawLogger();
#endif

		// Singleton
		[[nodiscard]] static Logger* GetInstance();
		static void DeleteInstance();

	private:
		struct S_LogData
		{
			E_LogType logType;
			std::string logContent;
		};

		static Logger* m_instance;
		std::vector<S_LogData> m_logStack;
		bool m_showLogError = true;
		bool m_showLogWarning = true;
		bool m_showLogInfo = true;
	};
}
