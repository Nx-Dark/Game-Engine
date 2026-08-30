#include "dpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Renderer2D.h"

namespace Dark {

	Renderer::SceneData* Renderer::s_SceneData{ new SceneData() };

	void Renderer::Init()
	{
		DARK_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::ShutDown()
	{
		DARK_PROFILE_FUNCTION();

		Renderer2D::ShutDown();
	}

	void Renderer::OnWindowResize(int width, int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
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
		shader->SetMat4("u_ProjectionView", s_SceneData->m_ProjectionViewMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}