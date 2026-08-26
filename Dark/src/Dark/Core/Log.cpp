#include "dpch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Dark {

	void Log::Init(){
		
		spdlog::set_pattern("%^[%d/%m/%Y][%T] - %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("DARK ENGINE");
		spdlog::set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
		spdlog::set_level(spdlog::level::trace);
			
	}

}