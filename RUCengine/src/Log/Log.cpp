#include "Log.h"

#ifdef RUC_WINDOWS
	#include "Platform/Windows/WindowsConsoleLogger.h"
#endif

namespace RUC
{
	std::vector<Logger*> Log::s_Loggers;

	Logger::Logger(bool autoFlush, LogSource sources, LogType ignored)
		:m_AutoFlush(autoFlush), m_Sources(sources), m_Ignored(ignored)
	{

	}

	Logger::~Logger()
	{

	}





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

	//TODO: read default loggers from file instead of the hardcoded version
	void Log::Init()
	{
		//Add default loggers if none has been specified by the client
		auto logger = AddConsoleLogger();
		logger->Log(LogType::LOG_ERROR, "Test");
	}
}
