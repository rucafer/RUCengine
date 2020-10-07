/*#pragma once

#include "Log/Log.h"
#include <Windows.h>

namespace RUC
{
	
	class WindowsConsoleLogger : public ConsoleLogger
	{
	public:
		WindowsConsoleLogger() = delete;
		WindowsConsoleLogger(bool autoFlush, LogSource sources, LogType ignored);

		~WindowsConsoleLogger() = default;

		void Log(LogType type, const std::string& message) override;
		void Flush() override;

	private:
		HANDLE m_handle;
		WORD m_DefaultColor;
		const WORD c_ErrorColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
		const WORD c_WarningColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		const WORD c_InfoColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	};
}*/