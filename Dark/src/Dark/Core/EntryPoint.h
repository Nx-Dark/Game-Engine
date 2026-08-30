#pragma once

#ifdef DARK_PLATFORM_WINDOWS

extern Dark::Application* Dark::CreateApplication();

int main(int argc, char** argv) {

	DARK_PROFILE_BEGIN_SESSION("Start-Up", "DarkEngine-Startup.json");
	Dark::Log::Init();

	DARK_CORE_WARN("Initialized!");
	DARK_CLIENT_WARN("Initialized!");

	Dark::Application* app{ Dark::CreateApplication() };
	DARK_PROFILE_END_SESSION();

	DARK_PROFILE_BEGIN_SESSION("Runtime", "DarkEngine-Runtime.json");
	app->Run();
	DARK_PROFILE_END_SESSION();

	DARK_PROFILE_BEGIN_SESSION("ShutDown", "DarkEngine-ShutDown.json");
	delete app;
	DARK_PROFILE_END_SESSION();

	return 0;

}

#endif