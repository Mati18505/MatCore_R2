#pragma once
#include <memory>

namespace spdlog {
	class logger;
}

class Log {
public:
	static void Init();

	static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
	static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
private:
	static std::shared_ptr<spdlog::logger> coreLogger;
	static std::shared_ptr<spdlog::logger> clientLogger;
};

#define LOG_CORE_TRACE(...)		::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)		::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)		::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)		::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...)	::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...)			::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)			::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)			::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)			::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)		::Log::GetClientLogger()->critical(__VA_ARGS__)