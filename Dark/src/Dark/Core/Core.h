#pragma once

#ifdef DARK_PLATFORM_WINDOWS
	#ifdef DARK_DYNAMIC_LINK
		#ifdef DARK_BUILD_DLL
			#define DARK_API __declspec(dllexport)
		#else 
			#define DARK_API __declspec(dllimport)
		#endif
	#else 
		#define DARK_API
	#endif
#else
	#error DARK ENGINE IS ONLY SUPPORTED FOR WINDOWS!
#endif

#ifdef DARK_DEBUG
	#define DARK_ENABLE_ASSERTS
#endif

#ifdef DARK_ENABLE_ASSERTS
	#define DARK_CORE_ASSERT(x, ...) { if(!(x)) {DARK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define DARK_CLIENT_ASSERT(x, ...) { if(!(x)) { DARK_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define DARK_CORE_ASSERT(x, ...)
	#define DARK_CLIENT_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define DARK_BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)

namespace Dark {

	template<typename T>
	using Ref = std::shared_ptr<T>; //Reference(std::shared_ptr)

	template<typename T>
	using Scope = std::unique_ptr<T>; //Scoped/raw(std::unique_ptr)

}