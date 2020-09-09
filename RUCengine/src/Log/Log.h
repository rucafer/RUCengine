#pragma once

#include <vector>
#include <string>
#include <stdio.h>
#include <ctime>

#include "base.h"

//main declaratino needed to make main a friend function
int main(int argc, char** argv);

namespace RUC
{
	enum class LogType : unsigned char
	{
		LOG_NONE	= 0,
		LOG_INFO	= 1 << 0,
		LOG_WARNING = 1 << 1,
		LOG_ERROR	= 1 << 2,
	};
	inline constexpr LogType operator|(LogType a, LogType b)
	{
		return (LogType)((unsigned char)a | (unsigned char)b);
	}


	enum class LogSource : unsigned char
	{
		CORE = 1 << 0,
		APP  = 1 << 1
	};
	inline constexpr LogSource operator|(LogSource a, LogSource b)
	{
		return (LogSource)((unsigned char)a | (unsigned char)b);
	}

	class RUCAPI Logger
	{
	public:
		//Defalut parameters are not provided
		Logger() = delete;
		Logger(bool autoFlush, LogSource sources, LogType ignored);
		virtual ~Logger();

		LogSource GetSources() { return m_Sources; }
		LogType GetIgnoredTypes() { return m_Ignored; }
		bool GetAutoFlush() { return m_AutoFlush; }

		void SetSources(LogSource sources) { m_Sources = sources; }
		void SetIgnoredTypes(LogType ignored) { m_Ignored = ignored; }
		void SetAutoFlush(bool autoFlush) { m_AutoFlush = autoFlush; }
	
	protected:
		/*
		* Token list
		* h: current time: hours
		* m: current time: minutes
		* s: current time: seconds
		* t: current time: hours:minutes:seconds
		* S: source: APP or CORE
		* #: # character: prints the # character instead of using it as the beginning of a token
		*/
		template<typename... Args>
		std::string format(const std::string& message, LogSource source, Args... args)
		{
			std::string result;
			const size_t messageSize = message.size();
			//Reserve memory to avoid allocations.
			result.reserve(messageSize);
			const char token = '#';
			size_t lastPos = -1;	//End of the last token found (or 0 if none was found)

			size_t pos = message.find(token);
			while (pos != std::string::npos)
			{
				if (pos == messageSize - 1)
				{
					return "Incorrect format, # character found at the end of the string\n";
				}
				result += message.substr(lastPos + 1, pos - (lastPos + 1));
				lastPos = pos + 1;	//The token end is the character after #

				//Add info depending on the token
				switch (message[lastPos])
				{
				case 'h':
				{
					time_t t = time(nullptr);
					tm buf;
					localtime_s(&buf, &t);
					result += std::to_string(buf.tm_hour);
					break;
				}
				case 'm':
				{
					//TODO: force string to have two digits
					time_t t = time(nullptr);
					tm buf;
					localtime_s(&buf, &t);
					result += std::to_string(buf.tm_min);
					break;
				}
				case 's':
				{
					time_t t = time(nullptr);
					tm buf;
					localtime_s(&buf, &t);
					result += std::to_string(buf.tm_sec);
					break;
				}
				case 'S':
					result += source == LogSource::APP ? "APP" : "CORE";
					break;
				default:
					return std::string("Incorrect format. Invalid token \"") + message.at(lastPos) + 
						"\" found at position " + std::to_string(lastPos) + '\n';
				}
				pos = message.find(token, lastPos);
			}
			
			result += message.substr(lastPos + 1, messageSize - (lastPos + 1));
			return result;
		}

	private:
		LogSource m_Sources;
		LogType m_Ignored;
		bool m_AutoFlush;
	};

	//Logger specification for each output type
	class RUCAPI ConsoleLogger : public Logger
	{
	public:
		//Defalut parameters are not provided
		ConsoleLogger() = delete;
		ConsoleLogger(bool autoFlush, LogSource sources, LogType ignored);
		virtual ~ConsoleLogger() = default;

		virtual void Log(LogType type, const std::string& message) = 0;
		virtual void Flush() = 0;
	};

	class Log
	{
	public:
		RUCAPI static ConsoleLogger* AddConsoleLogger(bool autoFlush = true, LogSource sources = LogSource::CORE | LogSource::APP,
			LogType ignored = LogType::LOG_NONE);
	private:
		static void Init();

		//Only main can initialize the log, so that the client can't initialize again.
		friend int ::main(int argc, char** argv);
	private:
		static std::vector<Logger*> s_Loggers;
	};
}