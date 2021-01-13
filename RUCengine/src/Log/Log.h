#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#ifdef RUC_DYNAMIC_LIBRARY

	#undef SPDLOG_API

	#ifdef RUC_CORE
		#define SPDLOG_API _declspec(dllexport)
	#else
		#undef SPDLOG_API
		#define SPDLOG_API _declspec(dllimport)
	#endif
#endif

namespace RUC
{
	class Log
	{
	public:
		static void Init();
		
		static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}