#pragma once

#include <glm/glm.hpp>

namespace Dark
{

	//this is just for the renderer. Renderer doesn't care abt ortho or perspective, it only needs a projection matrix
	class Camera
	{
	protected:

		glm::mat4 m_Projection{1.0f};

	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: m_Projection{projection} {}

		virtual ~Camera() = default;

		inline const glm::mat4& GetProjection() const { return m_Projection; }
	};

}