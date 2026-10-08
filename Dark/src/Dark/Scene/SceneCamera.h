#pragma once

#include "Dark/Renderer/Camera.h"

namespace Dark
{

	class SceneCamera : public Camera
	{
	private:
		float m_OrthographicSize{ 10.0f };
		float m_OrthographicNear{ -1.0f }, m_OrthographicFar{ 1.0f };

		float m_AspectRatio{ 1.0f };

	private:
		void RecalcProjection();

	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
		
		//size is going to be multiplied by the aspect ratio to get the width
		//height will be same as the size
		void SetOrthographic(float size, float nearClip = -1.0f, float farClip = 1.0f);
		void SetViewportSize(uint32_t width, uint32_t height);

		//getter and setter for orthographic size
		inline float GetOrthographicSize() const { return m_OrthographicSize; }
		inline void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalcProjection(); }
	};

}