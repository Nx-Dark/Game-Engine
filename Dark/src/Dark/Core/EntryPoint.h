#pragma once

#ifdef DARK_PLATFORM_WINDOWS

extern Dark::Application* Dark::CreateApplication();

int main(int argc, char** argv) {

	Dark::Log::Init();
	
	DARK_CORE_WARN("Initialized!");
	DARK_CLIENT_WARN("Initialized!");

	Dark::Application* app{ Dark::CreateApplication() };
	app->Run();
	delete app;

	return 0;

}

#endif