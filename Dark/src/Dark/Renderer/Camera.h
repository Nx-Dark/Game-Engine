#pragma once

#include <glm/glm.hpp>

namespace Dark
{
	class Camera
	{
	private:

		glm::mat4 m_Projection{1.0f};

	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: m_Projection{projection} {}

		inline const glm::mat4& GetProjection() const { return m_Projection; }
	};

}