#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#ifdef RUC_CORE
	#define RUC_TRACE(...)	RUC::Log::GetCoreLogger()->trace(__VA_ARGS__);
	#define RUC_INFO(...)		RUC::Log::GetCoreLogger()->info(__VA_ARGS__);
	#define RUC_WARN(...)		RUC::Log::GetCoreLogger()->warn(__VA_ARGS__);
	#define RUC_ERROR(...)	RUC::Log::GetCoreLogger()->error(__VA_ARGS__);
#else
	#define RUC_INFO(...)		RUC::Log::GetClientLogger()->info(__VA_ARGS__);
	#define RUC_WARN(...)		RUC::Log::GetClientLogger()->warn(__VA_ARGS__);
	#define RUC_TRACE(...)	RUC::Log::GetClientLogger()->trace(__VA_ARGS__);
	#define RUC_ERROR(...)	RUC::Log::GetClientLogger()->error(__VA_ARGS__);
#endif

namespace RUC
{
	class Log
	{
	public:
		static void Init();
		
		static std::shared_ptr<spdlog::logger> GetCoreLogger();
		static std::shared_ptr<spdlog::logger> GetClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}