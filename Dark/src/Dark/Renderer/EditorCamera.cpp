#include "dpch.h"
#include "EditorCamera.h"

#include "Dark/Core/Input.h"

namespace Dark
{
	EditorCamera::EditorCamera(const glm::vec3& position, uint32_t width, uint32_t height, float vFov_inRads, float nearClip, float farClip)
		: m_Position{ position }, m_ViewportWidth{ width }, m_ViewportHeight{ height }, m_Fov{ vFov_inRads }, m_NearClip{nearClip}, m_FarClip{farClip}
	{

		m_AspectRatio = (float)width / (float)height;

		//camera view matrix stuff;
		m_Target = { 0.0f, 0.0f, 0.0f };
		m_Up = { 0.0f, 1.0f, 0.0f };

		m_Forward = glm::normalize(m_Target - m_Position);
		m_Right = glm::normalize(glm::cross(m_Forward, m_Up));

		m_Up = glm::normalize(glm::cross(m_Right, m_Forward));

		m_Orientation = glm::quat{ glm::vec3{-m_Pitch, -m_Yaw, 0.0f} };

		CalcProjectionMat();
		CalcViewMat();
	}

	EditorCamera::~EditorCamera()
	{

	}

	void EditorCamera::OnUpdate(DeltaTime dt)
	{
		const glm::vec2& curMousePos { Input::GetMouseX(), Input::GetMouseY() };
		glm::vec2 mouseDelta{ (curMousePos - m_LastMousePos) * 0.1f };
		m_LastMousePos = curMousePos;

		if (Input::IsKeyPressed(KeyCode::KEY_LEFT_ALT))
		{
			if (Input::IsMouseButtonPressed(MouseCode::MOUSE_BUTTON_RIGHT))
				MousePan(dt, mouseDelta);
			else if (Input::IsMouseButtonPressed(MouseCode::MOUSE_BUTTON_MIDDLE))
				MouseRotate(dt, mouseDelta);
		}
		else if (Input::IsMouseButtonPressed(MouseCode::MOUSE_BUTTON_RIGHT))
		{
			Move(dt, mouseDelta);
		}

		CalcViewMat();
	}

	void EditorCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width, m_ViewportHeight = height;
		m_AspectRatio = (float)width / (float)height;

		//building projection
		CalcProjectionMat();
	}

	//movement
	void EditorCamera::Move(DeltaTime dt, const glm::vec2& mouseDelta)
	{
		const float m_speed{ m_MoveSpeed * dt };
		const float r_speed{ glm::radians(m_RotateSpeed) };

		glm::vec3 direction{};

		if (Input::IsKeyPressed(KeyCode::KEY_W))
			direction += glm::vec3{ m_Forward.x, 0.0f, m_Forward.z };
		if (Input::IsKeyPressed(KeyCode::KEY_S))
			direction -= glm::vec3{ m_Forward.x, 0.0f, m_Forward.z };
		if (Input::IsKeyPressed(KeyCode::KEY_D))
			direction += m_Right;
		if (Input::IsKeyPressed(KeyCode::KEY_A))
			direction -= m_Right;
		if (Input::IsKeyPressed(KeyCode::KEY_SPACE))
			direction += glm::vec3{ 0.0f, 1.0f, 0.0f };
		if (Input::IsKeyPressed(KeyCode::KEY_LEFT_SHIFT))
			direction -= glm::vec3{ 0.0f, 1.0f, 0.0f };

		m_Position += ((glm::length(direction) != 0.0f) ? glm::normalize(direction) : direction) * m_speed;

		//rotation
		m_Yaw += mouseDelta.x * r_speed;
		m_Pitch -= mouseDelta.y * r_speed;

		//constexpr float pitchLimit{ glm::radians(89.0f) };
		//m_Pitch = glm::clamp(m_Pitch, -pitchLimit, pitchLimit);

		UpdateOrientation();

	}

	void EditorCamera::MousePan(DeltaTime dt, const glm::vec2& mouseDelta)
	{
		const auto[panSeedX, panSpeedY] { CalcPanSpeed() };

		const glm::vec3 offset{
			m_Right * (-mouseDelta.x * panSeedX) +
			m_Up * (mouseDelta.y * panSpeedY)
		};

		m_Position += offset;
		m_Target += offset;
	}

	void EditorCamera::MouseRotate(DeltaTime dt, const glm::vec2& mouseDelta)
	{
		//will be implemented once mouse picking and stuff is done
	}
	
	void EditorCamera::UpdateOrientation()
	{
	
		//rotation using normal trig functions(gimbal lock)
		//const float sinYaw{ glm::sin(m_Yaw) };
		//const float cosYaw{ glm::cos(m_Yaw) };
		//const float sinPitch{ glm::sin(m_Pitch) };
		//const float cosPitch{ glm::cos(m_Pitch) };

		//m_Forward = glm::normalize(glm::vec3{
		//	sinYaw * cosPitch,
		//	sinPitch,
		//	-cosYaw * cosPitch
		//});

		//m_Right = glm::normalize(glm::cross(m_Forward, { 0.0f, 1.0f, 0.0f }));
		//m_Up = glm::normalize(glm::cross(m_Right, m_Forward));

		//rotation using quaternion(no gimbal lock);
		m_Orientation = glm::quat{ glm::vec3{m_Pitch, -m_Yaw, 0.0f} };
		m_Up = m_Orientation * glm::vec3{ 0.0f, 1.0f, 0.0f };
		m_Right = m_Orientation * glm::vec3{ 1.0f, 0.0f, 0.0f };
		m_Forward = m_Orientation * glm::vec3{ 0.0f, 0.0f, -1.0f };
	}


	//event related movement
	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher{ e };

		dispatcher.Dispatch<MouseScrolledEvent>(DARK_BIND_EVENT_FN(EditorCamera::OnMouseScrolled));
	}

	bool EditorCamera::OnMouseScrolled(MouseScrolledEvent& e)
	{
		//zooming the camera
		float y_Offset{ e.GetYOffset() };
		m_Fov -= y_Offset * glm::radians(m_ZoomSpeed);
		m_Fov = glm::clamp(m_Fov, glm::radians(24.0f), glm::radians(165.0f));
		CalcProjectionMat();

		return false;
	}
}