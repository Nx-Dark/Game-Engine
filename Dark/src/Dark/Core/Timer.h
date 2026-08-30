#pragma once

#include <chrono>

namespace Dark {

	class DARK_API Timer
	{

		inline static std::chrono::time_point<std::chrono::high_resolution_clock> s_StartTimePoint{ std::chrono::high_resolution_clock::now() };

	public:
		inline static void Init()
		{
			s_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		inline static float GetElapsedTime()
		{
			std::chrono::time_point<std::chrono::high_resolution_clock> cur_time{ std::chrono::high_resolution_clock::now() };
			std::chrono::duration<float, std::chrono::seconds::period> elapsed_time{ cur_time - s_StartTimePoint };
			return elapsed_time.count();
		}

	};

}