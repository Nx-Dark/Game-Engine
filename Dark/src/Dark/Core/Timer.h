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

	template<typename fn>
	class DARK_API ProfilingTimer
	{

		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint{};
		const char* m_Name{};
		bool m_Stopped{};
		fn Fn;

	public:
		ProfilingTimer(const char* name, fn&& func)
			: m_Name{ name }, Fn{ func }
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~ProfilingTimer()
		{
			if (!m_Stopped)
				Stop();
		}
		
		inline void Stop()
		{
			auto endTImePoint{ std::chrono::high_resolution_clock::now() };

			auto start_time{ std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count() };
			auto end_time{ std::chrono::time_point_cast<std::chrono::microseconds>(endTImePoint).time_since_epoch().count() };

			m_Stopped = true;

			float duration{ (end_time - start_time) * 0.001f };

			Fn({ m_Name, duration });
		}
	};

}