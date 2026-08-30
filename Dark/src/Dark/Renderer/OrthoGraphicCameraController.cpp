#include "dpch.h"
#include "OrthographicCameraController.h"

#include "Dark/Core/Input.h"

namespace Dark {

	OrthoGraphicCameraController::OrthoGraphicCameraController(float aspectRatio, float camSpeed, float camRotSped, bool camRotation)
		: m_AspectRatio{ aspectRatio }, m_Camera{ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel },
		m_CamTranslationSpeed{ camSpeed }, m_CamRotationSpeed{ camRotSped }, m_RotateCamera{ camRotation }
	{

	}

	void OrthoGraphicCameraController::OnUpdate(DeltaTime dt)
	{
		DARK_PROFILE_FUNCTION();

		//camera update
		if (Input::IsKeyPressed(DK_KEY_D)) { m_CamPos.x +=  m_CamTranslationSpeed * dt; }
		if (Input::IsKeyPressed(DK_KEY_A)) { m_CamPos.x -=  m_CamTranslationSpeed * dt; }
		if (Input::IsKeyPressed(DK_KEY_W)) { m_CamPos.y +=  m_CamTranslationSpeed * dt; }
		if (Input::IsKeyPressed(DK_KEY_S)) { m_CamPos.y -=  m_CamTranslationSpeed * dt; }

		if (m_RotateCamera) {
			if (Input::IsKeyPressed(DK_KEY_Q)) m_CamRotation += m_CamRotationSpeed * dt;
			if (Input::IsKeyPressed(DK_KEY_E)) m_CamRotation -= m_CamRotationSpeed * dt;
			m_Camera.SetRotation(m_CamRotation);
		}

		m_Camera.SetPosition(m_CamPos);
		//

		m_CamTranslationSpeed = m_ZoomLevel * 1.25f;
	}

	void OrthoGraphicCameraController::OnEvent(Event& e)
	{

		DARK_PROFILE_FUNCTION();

		EventDispatcher dispatcher{ e };

		dispatcher.Dispatch<MouseScrolledEvent>(DARK_BIND_EVENT_FN(OrthoGraphicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(DARK_BIND_EVENT_FN(OrthoGraphicCameraController::OnWindowResizeEvent));

	}

	bool OrthoGraphicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{

		DARK_PROFILE_FUNCTION();

		m_ZoomLevel -= (e.GetYOffset() * 0.25f);
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.05f, 10.0f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);

		return false;
	}

	bool OrthoGraphicCameraController::OnWindowResizeEvent(WindowResizeEvent& e)
	{

		DARK_PROFILE_FUNCTION();

		m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);

		return false;
	}

}