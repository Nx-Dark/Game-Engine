#include "dpch.h"
#include "Dark/Core/Window.h"

#ifdef DARK_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Dark
{
	Scope<Window> Window::Create(const WindowProps& props)
	{

	#ifdef DARK_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		DARK_CORE_ASSERT(false, "Unknown Platform!");
		return nullptr;
	#endif

	}
}