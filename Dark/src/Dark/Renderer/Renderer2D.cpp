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
		float texID{};
		float tilingFactor{};
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuadCount{ 10000 };
		static const uint32_t MaxVertexCount{ MaxQuadCount * 4 };
		static const uint32_t MaxIndexCount{ MaxQuadCount * 6 };
		static const uint32_t MaxTextureSlots{ 32 };

		Ref<VertexArray> VertexArray{};
		Ref<VertexBuffer> VertexBuffer{};
		Ref<Shader> TextureShader{};
		Ref<Texture2D> WhiteTexture{};

		uint32_t QuadIndexCount{};
		QuadVertex* QuadVertexBufferBase{ nullptr };
		QuadVertex* QuadVertexBufferPtr{ nullptr };

		glm::vec4 QuadVertexPositions[4];

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots{};
		uint32_t TextureSlotIndex{ 1 }; //0 -> is used for the whiteTexture

		Renderer2D::Statistics stats;

	};

	//stack instance of the required rendererData
	static Renderer2DData s_RendererData;

	//creating vertex helper function
	static const glm::vec2 s_TexCoordsLUT[4]
		{ glm::vec2{0.0f, 0.0f}, glm::vec2{1.0f, 0.0f}, glm::vec2{1.0f, 1.0f}, glm::vec2{0.0f, 1.0f} };

	static void CreateQuad(const ColorRect& colorRect, const glm::mat4& transform, float textureIndex, float tiling_factor)
	{
		for (int i{}; i < 4; i++)
		{
			s_RendererData.QuadVertexBufferPtr->pos = transform * s_RendererData.QuadVertexPositions[i];
			s_RendererData.QuadVertexBufferPtr->color = colorRect.color;
			s_RendererData.QuadVertexBufferPtr->texCoords = s_TexCoordsLUT[i];
			s_RendererData.QuadVertexBufferPtr->texID = textureIndex;
			s_RendererData.QuadVertexBufferPtr->tilingFactor = tiling_factor;
			s_RendererData.QuadVertexBufferPtr++;
		}

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.stats.QuadCount++;
	}
	static void CreateQuad(const Rect& rect, const glm::mat4& transform, const glm::vec4& tint, float textureIndex, float tiling_factor)
	{
		for (int i{}; i < 4; i++)
		{
			s_RendererData.QuadVertexBufferPtr->pos = transform * s_RendererData.QuadVertexPositions[i];
			s_RendererData.QuadVertexBufferPtr->color = tint;
			s_RendererData.QuadVertexBufferPtr->texCoords = s_TexCoordsLUT[i];
			s_RendererData.QuadVertexBufferPtr->texID = textureIndex;
			s_RendererData.QuadVertexBufferPtr->tilingFactor = tiling_factor;
			s_RendererData.QuadVertexBufferPtr++;
		}

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.stats.QuadCount++;
	}

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
			{"aTexCoords", ShaderDataType::Float2},
			{"aTexID", ShaderDataType::Float},
			{"aTilingFactor", ShaderDataType::Float}
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
		int32_t textureIndices[s_RendererData.MaxTextureSlots];
		for (int32_t i{}; i < s_RendererData.MaxTextureSlots; i++) textureIndices[i] = i;
		s_RendererData.TextureShader->SetIntv("u_Textures", s_RendererData.MaxTextureSlots, textureIndices);

		s_RendererData.TextureSlots[0] = s_RendererData.WhiteTexture;

		//setting up quad vertex positions(base unit positions)
		s_RendererData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
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

		s_RendererData.TextureSlotIndex = 1;
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
		//bind all the active textures(upto 32)
		for (uint32_t i{}; i < s_RendererData.TextureSlotIndex; i++)
			s_RendererData.TextureSlots[i]->Bind(i);

		//Issue the draw call
		RenderCommand::DrawIndexed(s_RendererData.VertexArray, s_RendererData.QuadIndexCount);

		s_RendererData.stats.DrawCalls++;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_RendererData.QuadIndexCount = 0;
		s_RendererData.QuadVertexBufferPtr = s_RendererData.QuadVertexBufferBase;

		s_RendererData.TextureSlotIndex = 1;

	}

	//colored quad
	void Renderer2D::DrawQuad(const ColorRect& colorRect)
	{
		DARK_PROFILE_FUNCTION();

		DrawQuad(colorRect, 0.0f);
	}

	void Renderer2D::DrawQuad(const ColorRect& colorRect, float depth)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount) 
		{
			FlushAndReset();
		}

		const float textureIndex{ 0.0f };
		const float tiling_factor{ 1.0f };
		
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect.position, depth})
				* glm::scale(glm::mat4{1.0f}, glm::vec3{colorRect.size.x, colorRect.size.y, 1.0f})
		};

		CreateQuad(colorRect, transform, textureIndex, tiling_factor);

#if 0
		//batching, so this is meaning less
		s_RendererData.TextureShader->SetFloat("u_TilingFactor", 1.0f);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect.position, depth})
			* glm::scale(glm::mat4{1.0f}, {colorRect.size, 1.0f}) };

		s_RendererData.TextureShader->SetMat4("u_Transform", transform);

		s_RendererData.WhiteTexture->Bind();
		s_RendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData.VertexArray);
#endif

	}

	//colored rotated quad
	void Renderer2D::DrawRotatedQuad(const ColorRect& colorRect, float angleInRads)
	{

		DrawRotatedQuad(colorRect, 0.0f, angleInRads);
	}

	void Renderer2D::DrawRotatedQuad(const ColorRect& colorRect, float depth, float angleInRads)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		float textureIndex{ 0.0f };
		float tiling_factor{ 1.0f };

		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect.position, depth})
				* glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
					* glm::scale(glm::mat4{1.0f}, glm::vec3{colorRect.size.x, colorRect.size.y, 1.0f})
		};

		CreateQuad(colorRect, transform, textureIndex, tiling_factor);

#if 0
		s_RendererData.TextureShader->SetFloat4("u_Color", colorRect.color);
		s_RendererData.TextureShader->SetFloat("u_TilingFactor", 1.0f);

		//Order -> TRS(Translation then Rotation then Scale)
		glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{colorRect.position, depth}) * glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4{1.0f}, {colorRect.size, 1.0f}) };

		s_RendererData.TextureShader->SetMat4("u_Transform", transform);

		s_RendererData.WhiteTexture->Bind();
		s_RendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererData.VertexArray);
#endif

	}

	//textured quad
	void Renderer2D::DrawQuad(const Rect& rect, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{

		DrawQuad(rect, 0.0f, texture, tint, tiling_factor);
	}

	void Renderer2D::DrawQuad(const Rect& rect, float depth, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		float textureIndex{ 0.0f };

		for (uint32_t i{}; i < s_RendererData.TextureSlotIndex; i++)
		{
			if ((*s_RendererData.TextureSlots[i]) == (*texture))
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}

		if (textureIndex == 0.0f) 
		{
			textureIndex = static_cast<float>(s_RendererData.TextureSlotIndex);
			s_RendererData.TextureSlots[s_RendererData.TextureSlotIndex] = texture;
			s_RendererData.TextureSlotIndex++;
			s_RendererData.TextureSlotIndex = std::clamp(s_RendererData.TextureSlotIndex, 1u, 31u);
		}

		//Setting Vertex Stuff;
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, glm::vec3{rect.position, depth})
				* glm::scale(glm::mat4{1.0f}, glm::vec3{rect.size.x, rect.size.y, 1.0f})
		};

		CreateQuad(rect, transform, tint, textureIndex, tiling_factor);

	}

	//textured rotated quad
	void Renderer2D::DrawRotatedQuad(const Rect& rect, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DrawRotatedQuad(rect, 0.0f, texture, angleInRads, tint, tiling_factor);
	}

	void Renderer2D::DrawRotatedQuad(const Rect& rect, float depth, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		float textureIndex{ 0.0f };

		for (uint32_t i{}; i < s_RendererData.TextureSlotIndex; i++)
		{
			if ((*s_RendererData.TextureSlots[i]) == (*texture))
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = static_cast<float>(s_RendererData.TextureSlotIndex);
			s_RendererData.TextureSlots[s_RendererData.TextureSlotIndex] = texture;
			s_RendererData.TextureSlotIndex++;
			s_RendererData.TextureSlotIndex = std::clamp(s_RendererData.TextureSlotIndex, 1u, 31u);
		}

		//Setting Vertex Stuff;
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, glm::vec3{rect.position, depth})
				* glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f}) 
					* glm::scale(glm::mat4{1.0f}, glm::vec3{rect.size.x, rect.size.y, 1.0f})
		};

		CreateQuad(rect, transform, tint, textureIndex, tiling_factor);

	}

	void Renderer2D::ResetStats()
	{
		memset(&s_RendererData.stats, 0, sizeof(Renderer2D::Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_RendererData.stats;
	}


}