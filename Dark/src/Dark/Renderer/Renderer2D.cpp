#include "dpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dark {

	struct Renderer2DData
	{
		Ref<VertexArray> VertexArray{};
		Ref<Shader> ColorShader{};
	};

	static Ref<Renderer2DData> s_RendererData{};

	void Renderer2D::Init()
	{
		s_RendererData = std::make_unique<Renderer2DData>();

		//square
		s_RendererData->VertexArray = Dark::VertexArray::Create();

		float vertices[12]{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
		};

		Dark::Ref<Dark::VertexBuffer> vertexBuffer{ Dark::VertexBuffer::Create(vertices, sizeof(vertices)) };

		Dark::BufferLayout layout
		{
			{"aPos", Dark::ShaderDataType::Float3},
		};

		vertexBuffer->SetLayout(layout);
		s_RendererData->VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6]{
			0, 1, 2, 2, 3, 0
		};

		Dark::Ref<Dark::IndexBuffer> indexBuffer{ Dark::IndexBuffer::Create(indices, 6) };
		s_RendererData->VertexArray->SetIndexBuffer(indexBuffer);

		//basic shader
		s_RendererData->ColorShader= Dark::Shader::Create("Basic", "Assets/Shaders/vert.glsl", "Assets/Shaders/frag.glsl");
	}

	void Renderer2D::ShutDown()
	{

	}

	void Renderer2D::BeginScene(const OrthoGraphicCamera& camera)
	{
		std::static_pointer_cast<OpenGLShader>(s_RendererData->ColorShader)->Bind();
		std::static_pointer_cast<OpenGLShader>(s_RendererData->ColorShader)->SetUniformMatrix("u_ProjectionView", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		//glm::mat4 transform{ 1.0f };
		//transform = glm::scale(transform, glm::vec3{ size, 0.0f });
		//transform = glm::translate(transform, glm::vec3{ pos, 0.0f });
		std::static_pointer_cast<OpenGLShader>(s_RendererData->ColorShader)->Bind();
		std::static_pointer_cast<OpenGLShader>(s_RendererData->ColorShader)->SetUniformFloat4("u_Color", color);
		std::static_pointer_cast<OpenGLShader>(s_RendererData->ColorShader)->SetUniformMatrix("u_Transform", glm::mat4{ 1.0f });

		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{

	}

}