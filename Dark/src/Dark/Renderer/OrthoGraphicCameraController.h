#pragma once

#include "Dark/Renderer/OrthographicCamera.h"
#include "Dark/Core/DeltaTime.h"
#include "Dark/Events/ApplicationEvent.h"
#include "Dark/Events/MouseEvent.h"

namespace Dark {

	class DARK_API OrthoGraphicCameraController
	{
	private:

		struct OrthographicCameraBounds
		{
			float Left, Right;
			float Bottom, Top;

			float GetWidth() { return Right - Left; }
			float GetHeight() { return Top - Bottom; }
		};
			
		float m_AspectRatio{};
		float m_ZoomLevel{ 1.0f };
		OrthographicCameraBounds m_Bounds;
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

		//getters & setters
		inline OrthoGraphicCamera& GetCamera() { return m_Camera; }
		inline const OrthoGraphicCamera& GetCamera() const { return m_Camera; }

		inline const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

		inline float GetZoomLevel() const { return m_ZoomLevel; }
		inline void SetZoomLevel(float level) { m_ZoomLevel = level; }
	
	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	};

}