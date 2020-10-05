#pragma once

#include <vector>
#include <string>
#include <stdio.h>
#include <ctime>

#include "base.h"
#include "Core/Application.h"


namespace RUC
{
	typedef unsigned char verbLevel;
	typedef unsigned char logSources;

	class RUCAPI Logger
	{
	public:
		Logger();
		Logger(verbLevel verbCutoff, logSources sources, std::string format, bool autoFlush);
		virtual ~Logger();

		logSources GetSources() { return m_Sources; }
		verbLevel GetVerbosityCutoff() { return m_VerbCutoff; }
		bool GetAutoFlush() { return m_AutoFlush; }

		void SetSources(logSources sources) { m_Sources = sources; }
		void SetVerbosityCutoff(verbLevel verbCutoff) { m_VerbCutoff = verbCutoff; }
		void SetAutoFlush(bool autoFlush) { m_AutoFlush = autoFlush; }
	
	protected:
		virtual void Log() = 0;
		virtual void Flush() = 0;

	private:
		void GetFormatTokens(const std::string& format);

	private:
		logSources m_Sources;
		verbLevel m_VerbCutoff;
		bool m_AutoFlush;

		size_t* m_TokenIndices;
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