/*#include "WindowsConsoleLogger.h"
#include <iostream>


namespace RUC
{
	WindowsConsoleLogger::WindowsConsoleLogger(bool autoFlush, LogSource sources, LogType ignored)
		:ConsoleLogger(autoFlush, sources, ignored)
	{
		m_handle = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO default_buffer_info;
		GetConsoleScreenBufferInfo(m_handle, &default_buffer_info);
		m_DefaultColor = default_buffer_info.wAttributes;
	}

	void WindowsConsoleLogger::Log(LogType type, const std::string& message)
	{
		std::cout << format("#S #h:#m:#s TestMessage", LogSource::CORE) << '\n';


		//SetConsoleTextAttribute(m_handle, c_ErrorColor);
		//std::cout << "Error test";
		//SetConsoleTextAttribute(m_handle, c_WarningColor);
		//std::cout << "Warning test" << std::endl;
		//SetConsoleTextAttribute(m_handle, c_InfoColor);
		//std::cout << "Info test" << std::endl;

		//Reset console values
		SetConsoleTextAttribute(m_handle, m_DefaultColor);
	}

	void WindowsConsoleLogger::Flush()
	{
		std::cout << std::flush;
	}
}*/