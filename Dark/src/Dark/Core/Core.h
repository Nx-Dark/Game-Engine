#pragma once

#ifdef _WIN32
	
	#ifdef _WIN64
		#define DARK_PLATFORM_WINDOWS
	#else
		#error "X86 windows Not Supported!"
	#endif

#elif defined(__APPLE__) || (__MACH__)
	#include <TargetConditionals.h>

	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Simulator is not Supported For Now"
	#elif TARGET_OS_IPHONE == 1
		#define DARK_PLATFORM_IOS
		#error "IOS is Not Supported For Now"
	#elif TARGET_OS_MAC == 1
		#define DARK_PLATFORM_MACOS
		#error "MACOS is Not Supported For Now"
	#else
		#error "Unknown Platform"
	#endif

#elif defined(__ANDROID__)
	#define DARK_PLATFORM_ANDROID
	#error "Android not Supported For Now"
#elif defined(__linux__)
	#define DARK_PLATFORM_LINUX
	#error "Linux not Supported For Now"

#else
	#define DARK_API
	#error "UnSupported Platform!"

#endif

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

#elif DARK_PLATFORM_ANDROID
	#ifdef DARK_DYNAMIC_LINK
		#ifdef DARK_BUILD_DLL
			#define DARK_API
		#else
			#define DARK_API
		#endif
	#else
		#define DARK_API
	#endif

#elif DARK_PLATFORM_LINUX
	#ifdef DARK_DYNAMIC_LINK
		#ifdef DARK_BUILD_DLL
			#define DARK_API
		#else
			#define DARK_API
		#endif
	#else
		#define DARK_API
	#endif

#else
	#error ""UnSupported Platform!""

#endif


#ifdef DARK_DEBUG
	#define DARK_ENABLE_ASSERTS

	#if defined(DARK_PLATFORM_WINDOWS)
		#define DARK_DEBUGBREAK() __debugbreak()
	#elif defined(DARK_PLATFORM_LINUX)
		#include <signal.h>
		#define DARK_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform Doesn't Support DebugBreak yet!"
	#endif
#endif

//TODO: Make DARK_CORE and DARK_CLIENT ASSERT macro to accept no additional arguments except condition and still assert!
#ifdef DARK_ENABLE_ASSERTS
	#define DARK_CORE_ASSERT(x, ...) { if(!(x)) {DARK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define DARK_CLIENT_ASSERT(x, ...) { if(!(x)) { DARK_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define DARK_CORE_ASSERT(x, ...)
	#define DARK_CLIENT_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define DARK_BIND_EVENT_FN(function) [this]<typename... Args>(Args&&... args) -> decltype(auto) { return this->function(std::forward<Args>(args)...); }

namespace Dark {

	template<typename T>
	using Ref = std::shared_ptr<T>; //Reference(std::shared_ptr)

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>; //Scoped/raw(std::unique_ptr)

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}