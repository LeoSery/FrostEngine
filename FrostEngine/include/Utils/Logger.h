#pragma once

/*
* \file Logger.h
* 
* \brief Header file for the Logger class.
*/

#include "Core/Internal/Export.h"

#include <vector>
#include <string>

/*!
* \namespace frost::utils
*
* \brief The namespace for FrostEngine's utils.
*/
namespace frost::utils
{
	/*!
	* \enum E_LogType
	* 
	* \brief The enum that manages the type of log.
	* 
	* \details types: Info, Warning, Error.
	*/
	enum class E_LogType
	{
		Info,
		Warning,
		Error
	};

	/*!
	* \class Logger
	* 
	* \brief The class that manages the Logger of the FrostEngine.
	* 
	* \details Log the Info, Warning and Error of the FrostEngine.
	*/
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

		/*
		* \struct S_LogData
		* 
		* \brief The struct that manages the log data.
		* 
		* \details S_LogData contains the log type and the log content.
		*/
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
