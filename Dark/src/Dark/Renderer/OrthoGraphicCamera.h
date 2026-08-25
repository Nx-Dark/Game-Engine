#pragma once

#include <glm/glm.hpp>

namespace Dark {

	class OrthoGraphicCamera
	{

	private:
		glm::mat4 m_ProjectionMatrix{1.0f};
		glm::mat4 m_ViewMatrix{1.0f};
		glm::mat4 m_ProjectionViewMatrix{1.0f};

		glm::vec3 m_Position{};
		float m_Rotation{}; //orthographic camera only needs to rotate around the z axis

	public:
		OrthoGraphicCamera(float left, float right, float top, float bottom);
		void SetProjection(float left, float right, float top, float bottom);

		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalcViewMatrix(); }
		inline const glm::vec3& GetPosition() const { return m_Position; }
		
		inline void ResetRotation() { m_Rotation = 0.0f; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalcViewMatrix(); }
		inline float GetRotation() { return m_Rotation; }

		//getters for the matrices
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

	private:
		//only needs to be called when the camera changes it position or the rotation, doesn't need to recalculated every frame
		void RecalcViewMatrix();

	};

}