#include "Base.h"
#include "Log.h"

#ifdef RUC_WINDOWS
	#include "Platform/Windows/WindowsConsoleLogger.h"
#endif

namespace RUC
{
	std::vector<Logger*> Log::s_Loggers;

	Logger::Logger(verbLevel verbCutoff, logSources sources, std::string format, bool autoFlush)
		: m_VerbCutoff(verbCutoff), m_Sources(sources), m_AutoFlush(autoFlush)
	{
		GetFormatTokens(format);
	}

	Logger::Logger()
		:Logger(0, RUC_LOG_SOURCE_ALL, "%m", true)
	{
	}

	Logger::~Logger()
	{

	}

	//FORMATTING HELPER FUNCTIONS
	void Logger::GetFormatTokens(const std::string& format)
	{
		//TODO Get token indices from format string
		//TODO Check that message token is included
	}

	/*



	ConsoleLogger::ConsoleLogger(bool autoFlush, LogSource sources, LogType ignored)
		: Logger(autoFlush, sources, ignored)
	{

	}

	ConsoleLogger* Log::AddConsoleLogger(bool autoFlush, LogSource sources, LogType ignored)
	{
#ifdef RUC_WINDOWS
		auto wcl = new WindowsConsoleLogger(autoFlush, sources, ignored);
		s_Loggers.push_back(wcl);
		return wcl;
#endif
	}
	*/

	//TODO: read default loggers from file instead of the hardcoded version
	void Log::Init()
	{
		//Add default loggers if none has been specified by the client
		//auto logger = AddConsoleLogger();
		//logger->Log(LogType::LOG_ERROR, "Test");
	}
}
