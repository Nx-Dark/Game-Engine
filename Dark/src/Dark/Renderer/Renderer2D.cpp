#include "dpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dark {

	struct Renderer2DData
	{
		Ref<VertexArray> VertexArray{};
		Ref<Shader> ColorShader{};
		Ref<Shader> TextureShader{};
	};

	static Ref<Renderer2DData> s_RendererData{};

	void Renderer2D::Init()
	{
		s_RendererData = std::make_unique<Renderer2DData>();

		//square
		s_RendererData->VertexArray = Dark::VertexArray::Create();

		float vertices[20]{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f, 0.0f,  1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f,  0.0f, 1.0f
		};

		Dark::Ref<Dark::VertexBuffer> vertexBuffer{ Dark::VertexBuffer::Create(vertices, sizeof(vertices)) };

		Dark::BufferLayout layout
		{
			{"aPos", Dark::ShaderDataType::Float3},
			{"aTexCoords", Dark::ShaderDataType::Float2}
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
			
		//texture shader
		s_RendererData->TextureShader = Dark::Shader::Create("Texture", "Assets/Shaders/texVert.glsl", "Assets/Shaders/texFrag.glsl");
		s_RendererData->TextureShader->Bind();
		s_RendererData->TextureShader->SetInt("u_Texutre", 0);
	}
	
	void Renderer2D::ShutDown()
	{

	}

	void Renderer2D::BeginScene(const OrthoGraphicCamera& camera)
	{
		s_RendererData->ColorShader->Bind();
		s_RendererData->ColorShader->SetMat4("u_ProjectionView", camera.GetProjectionViewMatrix());

		s_RendererData->TextureShader->Bind();
		s_RendererData->TextureShader->SetMat4("u_ProjectionView", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		s_RendererData->ColorShader->Bind();
		s_RendererData->ColorShader->SetFloat4("u_Color", color);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, pos)
			* glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f}) };

		s_RendererData->ColorShader->SetMat4("u_Transform", transform);

		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float angle)
	{
		DrawQuad({ pos.x, pos.y, -0.5f }, size, color, angle);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float angle)
	{
		s_RendererData->ColorShader->Bind();
		s_RendererData->ColorShader->SetFloat4("u_Color", color);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, pos) * glm::rotate(glm::mat4{1.0f}, glm::radians(angle), glm::vec3{0.0f, 0.0f, 1.0f} )
			* glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f}) };

		s_RendererData->ColorShader->SetMat4("u_Transform", transform);

		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture, tint);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint)
	{
		s_RendererData->TextureShader->Bind();
		s_RendererData->TextureShader->SetFloat4("u_TintColor", tint);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, pos)
			* glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f}) };

		s_RendererData->TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();
		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float angle)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture, tint, angle);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float angle)
	{
		s_RendererData->TextureShader->Bind();
		s_RendererData->TextureShader->SetFloat4("u_TintColor", tint);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, pos) * glm::rotate(glm::mat4{1.0f}, glm::radians(angle), glm::vec3{0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4{1.0f}, {size.x, size.y, 1.0f}) };

		s_RendererData->TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();
		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}


}