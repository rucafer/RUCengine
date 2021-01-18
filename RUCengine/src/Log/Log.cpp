#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace RUC
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared < spdlog::sinks::stdout_color_sink_st>());

		sinks[0]->set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = std::make_shared<spdlog::logger>("RUC", begin(sinks), end(sinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(sinks), end(sinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger> Log::GetCoreLogger() { return s_CoreLogger; }
	std::shared_ptr<spdlog::logger> Log::GetClientLogger() { return s_ClientLogger; }
}