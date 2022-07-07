#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
namespace MatCore {
	class Log {
	public:
		static void Init();

		static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};

	//critical: aplikacja przestaje dzia³aæ
	//Error : b³êdy odczytania pliku, kompilacji shader, gl error
	//Warn : coœ MO¯E Ÿle zadzia³aæ lub program siê wysypaæ
	//Info: things work
	//Trace :


#define LOG_CORE_TRACE(...)		::MatCore::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)		::MatCore::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)		::MatCore::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)		::MatCore::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...)	::MatCore::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...)			::MatCore::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)			::MatCore::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)			::MatCore::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)			::MatCore::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)		::MatCore::Log::GetClientLogger()->critical(__VA_ARGS__)
}