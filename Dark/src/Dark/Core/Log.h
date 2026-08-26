#pragma once

#include "Dark/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

//macros for Log functions(Core/Engine/Server)
#define DARK_CORE_ERROR(...)		::Dark::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DARK_CORE_WARN(...)			::Dark::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DARK_CORE_INFO(...)			::Dark::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DARK_CORE_TRACE(...)		::Dark::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DARK_CORE_CRITICAL(...)		::Dark::Log::GetCoreLogger()->critical(__VA_ARGS__)

//macros for Log Functions(Client/App)
#define DARK_CLIENT_ERROR(...)      ::Dark::Log::GetClientLogger()->error(__VA_ARGS__)
#define DARK_CLIENT_WARN(...)       ::Dark::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DARK_CLIENT_INFO(...)       ::Dark::Log::GetClientLogger()->info(__VA_ARGS__)
#define DARK_CLIENT_TRACE(...)      ::Dark::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DARK_CLIENT_CRITICAL(...)   ::Dark::Log::GetClientLogger()->critical(__VA_ARGS__)

namespace Dark {

	class DARK_API Log
	{

	private:

		static inline std::shared_ptr<spdlog::logger> s_CoreLogger{};
		static inline std::shared_ptr<spdlog::logger> s_ClientLogger{};
		
	public:

		static void Init();

		//inline functions to return the reference to corelogger and clientlogger object pointers
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	};

}

