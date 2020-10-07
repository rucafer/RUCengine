#pragma once

#include <vector>
#include <string>
#include <stdio.h>
#include <ctime>

#include "base.h"
#include "Core/Application.h"

//Logging function used only if the logger initialization failed (it's just a wrapper for printf function)
#define RUC_RAW_LOG(message, ...) printf(message"\n", __VA_ARGS__);

namespace RUC
{
	typedef unsigned char verbLevel;
	typedef unsigned char logSources;

	class RUCAPI Logger
	{
	public:
		Logger(std::string format = "%m", verbLevel verbCutoff = 0, logSources sources = RUC_LOG_SOURCE_ALL, bool autoFlush = true);
		virtual ~Logger();

		logSources GetSources() { return m_Sources; }
		verbLevel GetVerbosityCutoff() { return m_VerbCutoff; }
		bool GetAutoFlush() { return m_AutoFlush; }

		void SetSources(logSources sources) { m_Sources = sources; }
		void SetVerbosityCutoff(verbLevel verbCutoff) { m_VerbCutoff = verbCutoff; }
		void SetAutoFlush(bool autoFlush) { m_AutoFlush = autoFlush; }
	
	public:
		template<typename... Args>
		void Log(const std::string& message, Args... args) //TODO: add more args(verb, source...)
		{
			size_t stringSize = snprintf(nullptr, 0, message.c_str(), args...) + 1;
			char* formattedString = new char[stringSize];
			snprintf(formattedString, stringSize, message.c_str(), args...);

			LogImpl(GetLogFinalMessage(formattedString));
			delete[] formattedString;
		}

		virtual void Flush() {}		//Should be pure virtual, temporary definition provided for tests
	protected:
		//Should be pure virtual, temporary definition provided for tests
		virtual void LogImpl(const std::string& message)
		{
			printf("%s\n", message.c_str());
		}

	private:
		bool GetFormatTokens(const std::string& format);
		std::string GetLogFinalMessage(const std::string& message);

	private:
		logSources m_Sources;
		verbLevel m_VerbCutoff;
		bool m_AutoFlush;
		std::string m_Format;

		std::vector<size_t> m_TokenIndices;
	};

	/*//Logger specification for each output type
	class RUCAPI ConsoleLogger : public Logger
	{
	public:
		//Defalut parameters are not provided
		ConsoleLogger() = delete;
		ConsoleLogger(bool autoFlush, LogSource sources, LogType ignored);
		virtual ~ConsoleLogger() = default;

		virtual void Log(LogType type, const std::string& message) = 0;
		virtual void Flush() = 0;
	};*/

	class Log
	{
	public:
		/*RUCAPI static ConsoleLogger* AddConsoleLogger(bool autoFlush = true, LogSource sources = LogSource::CORE | LogSource::APP,
			LogType ignored = LogType::LOG_NONE);*/
	private:
		static void Init();

		//Only main can initialize the log, so that the client can't initialize again.
		friend class Application;
	private:
		static std::vector<Logger*> s_Loggers;
	};
}