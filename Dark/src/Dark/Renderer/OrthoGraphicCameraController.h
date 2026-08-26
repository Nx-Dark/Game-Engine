#pragma once

#include "Dark/Renderer/OrthographicCamera.h"
#include "Dark/Core/DeltaTime.h"
#include "Dark/Events/ApplicationEvent.h"
#include "Dark/Events/MouseEvent.h"

namespace Dark {

	class DARK_API OrthoGraphicCameraController
	{
	private:
			
		float m_AspectRatio{};
		float m_ZoomLevel{ 1.0f };
		OrthoGraphicCamera m_Camera;

		glm::vec3 m_CamPos{ 0.0f };
		float m_CamRotation{ 0.0f };
		float m_CamTranslationSpeed{};
		float m_CamRotationSpeed{};
		bool m_RotateCamera{};

	public:
		OrthoGraphicCameraController(float aspectRatio, float camSpeed, float camRotSpeed, bool camRotation = false);

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		//getters
		inline OrthoGraphicCamera& GetCamera() { return m_Camera; }
		inline const OrthoGraphicCamera& GetCamera() const { return m_Camera; }
	
	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	};

}