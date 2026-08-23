#include "dpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Dark {

	Renderer::SceneData* Renderer::s_SceneData{ new SceneData() };

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthoGraphicCamera& camera)
	{
		s_SceneData->m_ProjectionViewMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::static_pointer_cast<OpenGLShader>(shader)->SetUniformMatrix("u_ProjectionView", s_SceneData->m_ProjectionViewMatrix);
		std::static_pointer_cast<OpenGLShader>(shader)->SetUniformMatrix("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}