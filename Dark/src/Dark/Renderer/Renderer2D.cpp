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
		Ref<Shader> TextureShader{};
		Ref<Texture2D> WhiteTexture{};
	};

	static Renderer2DData* s_RendererData{};

	void Renderer2D::Init()
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData = new Renderer2DData();

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

		//white texture
		s_RendererData->WhiteTexture = Dark::Texture2D::Create(1, 1);
		uint32_t textureData = 0xffffffff;
		s_RendererData->WhiteTexture->SetData(&textureData, sizeof(textureData));

		//texture shader
		s_RendererData->TextureShader = Dark::Shader::Create("Texture", "Assets/Shaders/texVert.glsl", "Assets/Shaders/texFrag.glsl");
		s_RendererData->TextureShader->Bind();
		s_RendererData->TextureShader->SetInt("u_Texutre", 0);
	}
	
	void Renderer2D::ShutDown()
	{
		DARK_PROFILE_FUNCTION();

		delete s_RendererData;
	}

	void Renderer2D::BeginScene(const OrthoGraphicCamera& camera)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData->TextureShader->Bind();
		s_RendererData->TextureShader->SetMat4("u_ProjectionView", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::EndScene()
	{
		DARK_PROFILE_FUNCTION();

	}

	//colored quad
	void Renderer2D::DrawQuad(const Ref<ColorRect>& colorRect)
	{
		DARK_PROFILE_FUNCTION();

		DrawQuad(colorRect, -0.5f);
	}

	void Renderer2D::DrawQuad(const Ref<ColorRect>& colorRect, float depth)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData->TextureShader->SetFloat4("u_Color", colorRect->color);
		s_RendererData->TextureShader->SetFloat("u_TilingFactor", 1.0f);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect->position, depth})
			* glm::scale(glm::mat4{1.0f}, {colorRect->size, 1.0f}) };

		s_RendererData->TextureShader->SetMat4("u_Transform", transform);

		s_RendererData->WhiteTexture->Bind();
		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}

	//colored rotated quad
	void Renderer2D::DrawRotatedQuad(const Ref<ColorRect>& colorRect, float angleInRads)
	{

		DrawRotatedQuad(colorRect, -0.5f, angleInRads);
	}

	void Renderer2D::DrawRotatedQuad(const Ref<ColorRect>& colorRect, float depth, float angleInRads)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData->TextureShader->SetFloat4("u_Color", colorRect->color);
		s_RendererData->TextureShader->SetFloat("u_TilingFactor", 1.0f);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect->position, depth}) * glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4{1.0f}, {colorRect->size, 1.0f}) };

		s_RendererData->TextureShader->SetMat4("u_Transform", transform);

		s_RendererData->WhiteTexture->Bind();
		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}

	//textured quad
	void Renderer2D::DrawQuad(const Ref<Rect>& rect, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{

		DrawQuad(rect, -0.5f, texture, tint, tiling_factor);
	}

	void Renderer2D::DrawQuad(const Ref<Rect>& rect, float depth, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData->TextureShader->SetFloat4("u_Color", tint);
		s_RendererData->TextureShader->SetFloat("u_TilingFactor", tiling_factor);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{rect->position, depth})
			* glm::scale(glm::mat4{1.0f}, {rect->size, 1.0f}) };

		s_RendererData->TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();
		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}

	//textured rotated quad
	void Renderer2D::DrawRotatedQuad(const Ref<Rect>& rect, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DrawRotatedQuad(rect, -0.5f, texture, angleInRads, tint, tiling_factor);
	}

	void Renderer2D::DrawRotatedQuad(const Ref<Rect>& rect, float depth, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData->TextureShader->SetFloat4("u_Color", tint);
		s_RendererData->TextureShader->SetFloat("u_TilingFactor", tiling_factor);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{rect->position, depth}) * glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4{1.0f}, {rect->size, 1.0f}) };

		s_RendererData->TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();
		s_RendererData->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData->VertexArray);
	}


}