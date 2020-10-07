#include "Base.h"
#include "Log.h"

#ifdef RUC_WINDOWS
	#include "Platform/Windows/WindowsConsoleLogger.h"
#endif

namespace RUC
{
	std::vector<Logger*> Log::s_Loggers;

	Logger::Logger(std::string format, verbLevel verbCutoff, logSources sources, bool autoFlush)
		: m_Format(format), m_VerbCutoff(verbCutoff), m_Sources(sources), m_AutoFlush(autoFlush)
	{

		if (!GetFormatTokens(format))
		{
			RUC_RAW_LOG("Logger format error, using default one (\"%%m\")");
			m_Format = "%m";
			m_TokenIndices = { 1 };
		}
	}

	Logger::~Logger()
	{
		Flush();
	}

	//FORMATTING HELPER FUNCTIONS

	/*
		* Token list
		* h: current time: hours (24h format)
		* H: current time: hours (12h format)
		* m: current time: minutes
		* s: current time: seconds
		* t: current time: hours:minutes:seconds: am/pm
		* T: current time: hours:minutes:seconds (24h format)
		* S: source: APP or CORE
		* %: & character: prints the % character instead of using it as the beginning of a token
	*/

	std::string Logger::GetLogFinalMessage(const std::string& message)
	{
		std::string result = "";
		//Beginning of the first substring to be printed
		size_t substrBeginning = 0;
		for (size_t tokenPos : m_TokenIndices)
		{
			result += m_Format.substr(substrBeginning, (tokenPos - 1) - substrBeginning);
			switch (m_Format.at(tokenPos))
			{
			case 'm':
				result += message;
					break;
			}
			substrBeginning = tokenPos + 1;
		}
		result += m_Format.substr(substrBeginning, m_Format.length() - substrBeginning);
		return result;
	}

	//Returns true if the Format is correct
	bool Logger::GetFormatTokens(const std::string& format)
	{
		//TODO: check that all tokens exists
		bool messageTokenFound = false;	//True if the message token (required) was found

		const char tokenHeader = '%';
		
		size_t tokenPos = format.find(tokenHeader);

		while (tokenPos != std::string::npos)
		{
			//If "%" is the last character, the last token is incomplete
			if (tokenPos != format.length() - 1)
			{
				//The token is the character after "%"
				m_TokenIndices.push_back(tokenPos + 1);

				if (!messageTokenFound && format.at(tokenPos + 1) == 'm')
				{
					messageTokenFound = true;
				}

				//The next search should start after this token (header+identifier)
				tokenPos += 2;
				tokenPos = format.find(tokenHeader, tokenPos);
			}
			else
			{
				RUC_RAW_LOG("Logger format: \"%s\" contains an incomplete token (\"%%\" shouldn't be the last character)", format.c_str());
				return false;
			}
		}

		if (!messageTokenFound)
		{
			RUC_RAW_LOG("Logger format: \"%s\" must contain a message token (%%m)", format.c_str());
		}
		return messageTokenFound;
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
		auto logger = new Logger("ABC%mDEF");
		logger->Log("123");
		//Add default loggers if none has been specified by the client
		//auto logger = AddConsoleLogger();
		//logger->Log(LogType::LOG_ERROR, "Test");
	}
}
