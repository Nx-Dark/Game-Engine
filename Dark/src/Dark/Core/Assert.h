#pragma once

#include "Dark/Core/Core.h"
#include "Dark/Core/Log.h"

#ifdef DARK_ENABLE_ASSERTS
	
	namespace Dark::Assert
	{

		//returns the simple file name;
		constexpr const char* CurrentFileName(const char* path)
		{
			const char* file{ path };

			while (*path != '\0')
			{
				if (*path == '/' || *path == '\\')
					file = ++path;
				else
					path++;
			}

			return file;
		}
		
	}

	#define DARK_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { DARK##type##ERROR(msg, __VA_ARGS__); DARK_DEBUGBREAK(); } }
	#define DARK_INTERNAL_ASSERT_WITH_MSG(type, check, ...) DARK_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define DARK_INTERNAL_ASSERT_NO_MSG(type, check) DARK_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", DARK_STRINGIFY_MACRO(check), ::Hazel::Assert::CurrentFileName(__FILE__), __LINE__)

	#define DARK_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define DARK_INTERNAL_ASSERT_GET_MACRO(...) DARK_EXPAND_MACRO( DARK_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, DARK_INTERNAL_ASSERT_WITH_MSG, DARK_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define DARK_ASSERT(...) DARK_EXPAND_MACRO( DARK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define DARK_CORE_ASSERT(...) DARK_EXPAND_MACRO( DARK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define DARK_ASSERT(...)
	#define DARK_CORE_ASSERT(...)
#endif