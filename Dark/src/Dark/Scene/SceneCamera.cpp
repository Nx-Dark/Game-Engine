#include "dpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dark
{

	SceneCamera::SceneCamera()
	{
		RecalcProjection();
	}

	void SceneCamera::RecalcProjection()
	{
		switch (m_ProjectionType)
		{
			case ProjectionType::Orthographic: 
			{
				float orthoLeft{ m_OrthographicSize * (m_AspectRatio * -0.5f) };
				float orthoRight{ m_OrthographicSize * (m_AspectRatio * 0.5f) };
				float orthoBottom{ m_OrthographicSize * -0.5f };
				float orthoTop{ m_OrthographicSize * 0.5f };

				m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop,
					m_OrthographicNear, m_OrthographicFar);
				break;
			}

			case ProjectionType::Perspective:
			{
				m_Projection = glm::perspective(m_PerspectiveVerticalFov, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
				break;
			}
		}
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalcProjection();
	}

	void SceneCamera::SetPerspective(float verticalFov, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveVerticalFov = verticalFov;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;

		RecalcProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width, m_ViewportHeight = height;
		m_AspectRatio = (float)width / (float)height;
		RecalcProjection();
	}

}