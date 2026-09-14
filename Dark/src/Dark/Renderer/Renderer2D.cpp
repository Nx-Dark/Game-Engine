#include "dpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dark {

	struct QuadVertex
	{
		glm::vec3 pos{};
		glm::vec4 color{};
		glm::vec2 texCoords{};
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuadCount{ 10000 };
		const uint32_t MaxVertexCount{ MaxQuadCount * 4 };
		const uint32_t MaxIndexCount{ MaxQuadCount * 6 };

		Ref<VertexArray> VertexArray{};
		Ref<VertexBuffer> VertexBuffer{};
		Ref<Shader> TextureShader{};
		Ref<Texture2D> WhiteTexture{};

		uint32_t QuadIndexCount{};
		QuadVertex* QuadVertexBufferBase{ nullptr };
		QuadVertex* QuadVertexBufferPtr{ nullptr };
	};

	static Renderer2DData s_RendererData;

	void Renderer2D::Init()
	{
		DARK_PROFILE_FUNCTION();

		//square
		s_RendererData.VertexArray = VertexArray::Create();

		s_RendererData.VertexBuffer = VertexBuffer::Create(s_RendererData.MaxVertexCount * sizeof(QuadVertex));

		BufferLayout layout
		{
			{"aPos", ShaderDataType::Float3},
			{"aColor", ShaderDataType::Float4},
			{"aTexCoords", ShaderDataType::Float2}
		};

		s_RendererData.VertexBuffer->SetLayout(layout);
		s_RendererData.VertexArray->AddVertexBuffer(s_RendererData.VertexBuffer);

		s_RendererData.QuadVertexBufferBase = new QuadVertex[s_RendererData.MaxVertexCount];

		uint32_t* indices{ new uint32_t[s_RendererData.MaxIndexCount] };

		uint32_t offset{};
		for (size_t i{}; i < s_RendererData.MaxIndexCount; i+=6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer{ IndexBuffer::Create(indices, s_RendererData.MaxIndexCount) };
		s_RendererData.VertexArray->SetIndexBuffer(indexBuffer);
		delete[] indices;

		//white texture
		s_RendererData.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t textureData = 0xffffffff;
		s_RendererData.WhiteTexture->SetData(&textureData, sizeof(textureData));

		//texture shader
		s_RendererData.TextureShader = Shader::Create("Texture", "Assets/Shaders/texVert.glsl", "Assets/Shaders/texFrag.glsl");
		s_RendererData.TextureShader->Bind();
		s_RendererData.TextureShader->SetInt("u_Texutre", 0);
	}
	
	void Renderer2D::ShutDown()
	{
		DARK_PROFILE_FUNCTION();

	}

	void Renderer2D::BeginScene(const OrthoGraphicCamera& camera)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData.TextureShader->Bind();
		s_RendererData.TextureShader->SetMat4("u_ProjectionView", camera.GetProjectionViewMatrix());

		s_RendererData.QuadIndexCount = 0;
		s_RendererData.QuadVertexBufferPtr = s_RendererData.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		DARK_PROFILE_FUNCTION();
		
		uint32_t dataSize = (uint8_t*)s_RendererData.QuadVertexBufferPtr - (uint8_t*)s_RendererData.QuadVertexBufferBase;
		s_RendererData.VertexBuffer->UploadData(s_RendererData.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_RendererData.VertexArray, s_RendererData.QuadIndexCount);
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

		//Setting Vertex Stuff;
		s_RendererData.QuadVertexBufferPtr->pos = { colorRect->position, depth };
		s_RendererData.QuadVertexBufferPtr->color = colorRect->color;
		s_RendererData.QuadVertexBufferPtr->texCoords = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->pos = { colorRect->position.x + colorRect->size.x, colorRect->position.y, depth };
		s_RendererData.QuadVertexBufferPtr->color = colorRect->color;
		s_RendererData.QuadVertexBufferPtr->texCoords = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->pos = { colorRect->position + colorRect->size, depth };
		s_RendererData.QuadVertexBufferPtr->color = colorRect->color;
		s_RendererData.QuadVertexBufferPtr->texCoords = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr++;
		 
		s_RendererData.QuadVertexBufferPtr->pos = { colorRect->position.x, colorRect->position.y + colorRect->size.y, depth };
		s_RendererData.QuadVertexBufferPtr->color = colorRect->color;
		s_RendererData.QuadVertexBufferPtr->texCoords = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr++;
		//***********************************//

		s_RendererData.QuadIndexCount += 6;

		//batching, so this is meaning less
		//s_RendererData.TextureShader->SetFloat("u_TilingFactor", 1.0f);

		////Order -> TRS(Translation then Rotation then Scale)
		//glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect->position, depth})
		//	* glm::scale(glm::mat4{1.0f}, {colorRect->size, 1.0f}) };

		//s_RendererData.TextureShader->SetMat4("u_Transform", transform);

		//s_RendererData.WhiteTexture->Bind();
		//s_RendererData.VertexArray->Bind();
		//RenderCommand::DrawIndexed(s_RendererData.VertexArray);
	}

	//colored rotated quad
	void Renderer2D::DrawRotatedQuad(const Ref<ColorRect>& colorRect, float angleInRads)
	{

		DrawRotatedQuad(colorRect, -0.5f, angleInRads);
	}

	void Renderer2D::DrawRotatedQuad(const Ref<ColorRect>& colorRect, float depth, float angleInRads)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData.TextureShader->SetFloat4("u_Color", colorRect->color);
		s_RendererData.TextureShader->SetFloat("u_TilingFactor", 1.0f);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect->position, depth}) * glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4{1.0f}, {colorRect->size, 1.0f}) };

		s_RendererData.TextureShader->SetMat4("u_Transform", transform);

		s_RendererData.WhiteTexture->Bind();
		s_RendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData.VertexArray);
	}

	//textured quad
	void Renderer2D::DrawQuad(const Ref<Rect>& rect, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{

		DrawQuad(rect, -0.5f, texture, tint, tiling_factor);
	}

	void Renderer2D::DrawQuad(const Ref<Rect>& rect, float depth, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData.TextureShader->SetFloat4("u_Color", tint);
		s_RendererData.TextureShader->SetFloat("u_TilingFactor", tiling_factor);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{rect->position, depth})
			* glm::scale(glm::mat4{1.0f}, {rect->size, 1.0f}) };

		s_RendererData.TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();
		s_RendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData.VertexArray);
	}

	//textured rotated quad
	void Renderer2D::DrawRotatedQuad(const Ref<Rect>& rect, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DrawRotatedQuad(rect, -0.5f, texture, angleInRads, tint, tiling_factor);
	}

	void Renderer2D::DrawRotatedQuad(const Ref<Rect>& rect, float depth, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		s_RendererData.TextureShader->SetFloat4("u_Color", tint);
		s_RendererData.TextureShader->SetFloat("u_TilingFactor", tiling_factor);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{rect->position, depth}) * glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4{1.0f}, {rect->size, 1.0f}) };

		s_RendererData.TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();
		s_RendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData.VertexArray);
	}


}