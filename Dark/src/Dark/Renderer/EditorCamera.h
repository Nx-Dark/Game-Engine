#pragma once

#include "Camera.h"
#include "Dark/Core/DeltaTime.h"
#include "Dark/Events/Event.h"
#include "Dark/Events/MouseEvent.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Dark
{

	class EditorCamera : public Camera
	{
	private:

		glm::vec3 m_Position{};
		glm::vec3 m_Target{};
		glm::vec3 m_Up{};
		glm::vec3 m_Right{};
		glm::vec3 m_Forward{};
		glm::quat m_Orientation{}; //represents the rotation of the camera's local axes;
		glm::mat4 m_ViewMat{1.0f};
		float m_Pitch{}, m_Yaw{}; //yaw is rotation around y axis and pitch is rotation around x axis;

		//camera viewport stuff
		uint32_t m_ViewportWidth{}, m_ViewportHeight{};
		float m_AspectRatio{};
		float m_Fov{};
		float m_NearClip{}, m_FarClip{};

		//movement stuff
		float m_MoveSpeed{ 5.0f };
		float m_RotateSpeed{ 4.0f };
		float m_ZoomSpeed{ 5.0f }; //5degrees per scroll is the speed;

		glm::vec2 m_LastMousePos{};

		//mouse state
		bool m_IsMouseLocked{};

	public:
		EditorCamera() = default;
		EditorCamera(const glm::vec3& position, uint32_t width, uint32_t height, float vFov_inRads, float nearClip, float farClip);
		EditorCamera(const EditorCamera& other) = default;
 		virtual ~EditorCamera();

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		//shitty getters and setters
		void SetViewportSize(uint32_t width, uint32_t height);
		inline std::pair<uint32_t, uint32_t> GetViewportSize() const { return { m_ViewportWidth, m_ViewportHeight }; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; CalcViewMat(); }
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetYFov(float fov) { m_Fov = fov; CalcProjectionMat(); }
		inline float GetYFov() const { return m_Fov; }
		inline void SetNearClip(float clip) { m_NearClip = clip;  CalcProjectionMat(); }
		inline void SetFarClip(float clip) { m_FarClip = clip;  CalcProjectionMat(); }
		inline float GetNearClip() const { return m_NearClip; }
		inline float GetFarClip() const { return m_FarClip; }
		inline void SetMoveSpeed(float val) { m_MoveSpeed = val; }
		inline float GetMoveSpeed() const { return m_MoveSpeed; }
		inline void SetRotateSpeed(float val) { m_RotateSpeed = val; }
		inline float GetRotateSpeed() const { return m_RotateSpeed; }
		inline void SetZoomSpeed(float val) { m_ZoomSpeed = val; }
		inline float GetZoomSpeed() const { return m_ZoomSpeed; }

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMat; }
		inline glm::mat4 GetViewProjMatrix() const { return m_Projection * m_ViewMat; }

	private:
		void Move(DeltaTime dt, const glm::vec2& mouseDelta);
		void MousePan(DeltaTime dt, const glm::vec2& mouseDelta);
		void MouseRotate(DeltaTime dt, const glm::vec2& mouseDelta);

		void UpdateOrientation();

		//
		inline void CalcProjectionMat() { m_Projection = glm::perspective(m_Fov, m_AspectRatio, m_NearClip, m_FarClip); }
		inline void CalcViewMat() { m_ViewMat = glm::lookAt(m_Position, m_Position + m_Forward, m_Up); }
		inline std::pair<float, float> CalcPanSpeed()
		{
			float x{ std::min(m_ViewportWidth / 1000.0f, 3.0f) };
			float y{ std::min(m_ViewportHeight / 1000.0f, 3.0f) };

			float xFactor{ 0.036f * (x * x) + 0.025f * x + 0.0302f };
			float yFactor{ 0.036f * (y * y) + 0.025f * y + 0.0302f };

			return { xFactor, yFactor };
		}

		//event related func
		bool OnMouseScrolled(MouseScrolledEvent& e);
	};

}