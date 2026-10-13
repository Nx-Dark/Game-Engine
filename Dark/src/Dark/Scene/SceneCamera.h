#pragma once

#include "Dark/Renderer/Camera.h"

namespace Dark
{

	class SceneCamera : public Camera
	{
	public:
		
		enum class ProjectionType { Orthographic = 0, Perspective = 1 };

	private:

		ProjectionType m_ProjectionType{ ProjectionType::Orthographic };

		//orthographic

		float m_OrthographicSize{ 10.0f };
		float m_OrthographicNear{ -1.0f }, m_OrthographicFar{ 1.0f };

		//perspective;

		float m_PerspectiveVerticalFov{ glm::radians(45.0f) }; //in radians
		float m_PerspectiveNear{ 0.01f }, m_PerspectiveFar{ 10000.0f };

		float m_AspectRatio{ 1.0f };

	private:
		void RecalcProjection();

	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
		
		void SetViewportSize(uint32_t width, uint32_t height);

		//orthographic shit
		//size is going to be multiplied by the aspect ratio to get the width
		//height will be same as the size
		void SetOrthographic(float size, float nearClip = -1.0f, float farClip = 1.0f);
		//getter and setter for orthographic size
		inline float GetOrthographicSize() const { return m_OrthographicSize; }
		inline void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalcProjection(); }
		//getters and setters for orthographic n/f clips
		inline float GetOrthographicNearClip() const { return m_OrthographicNear; }
		inline void SetOrthographicNearClip(float clip) { m_OrthographicNear = clip; RecalcProjection(); }
		inline float GetOrthographicFarClip() const { return m_OrthographicFar; }
		inline void SetOrthographicFarClip(float clip) { m_OrthographicFar = clip; RecalcProjection(); }

		//perspective shit
		inline void SetPerspective(float fov, float nearClip = 0.01f, float farClip = 10000.0f);
		//fov is in radians
		inline float GetPerspectiveVerticalFov() const { return m_PerspectiveVerticalFov; }
		inline void SetPerspectiveVerticalFov(float fov_inRads) { m_PerspectiveVerticalFov = fov_inRads; RecalcProjection(); }
		inline float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		inline void SetPerspectiveNearClip(float clip) { m_PerspectiveNear = clip; RecalcProjection(); }
		inline float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		inline void SetPerspectiveFarClip(float clip) { m_PerspectiveFar = clip; RecalcProjection(); }

		//getters and setters for the projection type
		inline ProjectionType GetProjectionType() const { return m_ProjectionType; }
		inline void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalcProjection(); }
	};

}