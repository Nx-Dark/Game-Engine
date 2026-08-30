#include "dpch.h"
#include "OrthoGraphicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dark {

	OrthoGraphicCamera::OrthoGraphicCamera(float left, float right, float top, float bottom)
		: m_ProjectionMatrix{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthoGraphicCamera::SetProjection(float left, float right, float top, float bottom)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthoGraphicCamera::RecalcViewMatrix()
	{
		DARK_PROFILE_FUNCTION();

		glm::mat4 transform{ glm::rotate(glm::mat4{1.0f}, glm::radians(m_Rotation), glm::vec3{0.0f, 0.0f, 1.0f}) * glm::translate(glm::mat4{1.0f}, m_Position) };

		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}