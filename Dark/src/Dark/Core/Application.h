#pragma once

#include "Dark/Core/Core.h"

#include "Dark/Core/Layer.h"
#include "Dark/Core/LayerStack.h"

#include "Dark/Events/Event.h"

#include "Dark/Core/Window.h"

#include "Dark/ImGui/ImGuiLayer.h"

#include "Dark/Renderer/OrthoGraphicCamera.h"

#include "Dark/Audio/AudioMixer.h"

namespace Dark {

	class DARK_API Application {

		//static instance of the application to access it from anywhere
		static Application* s_Instance;

		Scope<Window> m_Window;
		bool m_Running{true}, m_Minimized{false};

		//layer stack
		LayerStack m_LayerStack;

		//imgui layer
		ImGuiLayer* m_ImGuiLayer{};

		//audio shit
		Ref<AudioMixer> m_AudioMixer{};

		//time stuff
		float m_lastFrameTime{};
	public:

		Application(const std::string& appName = "Dark-Engine", uint32_t width = 960u, uint32_t height = 540u);
		virtual ~Application();

		void Run();

		//Event
		void OnEvent(Event& e);

		//layer stack
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		//get imguilayer
		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		//function to get the window
		inline Window& GetWindow() { return *m_Window; }

		//close function
		inline void Close() { m_Running = false; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	public:
		//accessing application from anywhere
		inline static Application& Get() { return *s_Instance; }
	};

	//To be defined in CLIENT!
	Application* CreateApplication();

}