#pragma once

#include "Engine/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace engine
{
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define ENGINE_CORE_TRACE(...)		::engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)		::engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)		::engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)		::engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...)	::engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define ENGINE_TRACE(...)			::engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...)			::engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...)			::engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)			::engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...)		::engine::Log::GetClientLogger()->critical(__VA_ARGS__)
