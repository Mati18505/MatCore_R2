#include "pch.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> MatCore::Log::coreLogger;
std::shared_ptr<spdlog::logger> MatCore::Log::clientLogger;

void MatCore::Log::Init() {
	spdlog::set_pattern("%^[%T] %n: %v%$");
	coreLogger = spdlog::stdout_color_mt("MatCore");
	coreLogger->set_level(spdlog::level::trace);

	clientLogger = spdlog::stdout_color_mt("APP");
	clientLogger->set_level(spdlog::level::trace);
}