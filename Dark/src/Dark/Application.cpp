#include "dpch.h"

#include "Application.h"

#include "Dark/Events/ApplicationEvent.h"

#include "Dark/Input.h"

#include "Dark/Core/Timer.h"

#include "Dark/Core/DeltaTime.h"

#include "Dark/Renderer/Renderer.h"

namespace Dark {
	Application* Application::s_Instance{ nullptr };

	Application::Application()
	{

		DARK_CORE_ASSERT(!s_Instance, "Application Already Exists");
		s_Instance = this;

		//creating window
		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallBackFn(DARK_BIND_EVENT_FN(Application::OnEvent));
		//m_Window->SetVsync(false);

		//initializing the renderer
		Renderer::Init();

		//creating the imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//timer
		Timer::Init();
		m_lastFrameTime = Timer::GetElapsedTime();
		
	}

	Application::~Application() {

	}

	void Application::Run() {

		while(m_Running) {

			//******Delta Time Stuff*************************//
			float curTime{ Timer::GetElapsedTime() };
			DeltaTime delatTime{ curTime - m_lastFrameTime };
			m_lastFrameTime = curTime;
			//***********************************************//

			//layer update
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(delatTime);
			}

			//imgui rendering for the layers
			m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			m_ImGuiLayer->End();


			//window update
			m_Window->OnUpdate();
		}

	}

	//Event
	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher{ e }; //event dispatcher

		//Window closing event dispatch
		dispatcher.Dispatch<WindowCloseEvent>([this](const WindowCloseEvent& e) -> bool {
			m_Running = false;
			return true;
		});

		////layer event handling
		for (auto it{ m_LayerStack.rbegin() }; it != m_LayerStack.rend(); it++) {
			(*it)->OnEvent(e);
			if (e.Handled()) break;
		}

	}

	//layer stack
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	//TODO: Pop wrappers for the LayerStack

}