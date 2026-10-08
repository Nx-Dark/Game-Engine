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
	static constexpr glm::vec2 s_TexCoordsLUT[4]
		{ glm::vec2{0.0f, 0.0f}, glm::vec2{1.0f, 0.0f}, glm::vec2{1.0f, 1.0f}, glm::vec2{0.0f, 1.0f} };

	//for colored quads
	static void CreateQuad(const glm::vec4& color, const glm::mat4& transform)
	{

		constexpr float textureIndex{ 0.0f };
		constexpr float tiling_factor{ 1.0f };

		for (int i{}; i < 4; i++)
		{
			s_RendererData.QuadVertexBufferPtr->pos = transform * s_RendererData.QuadVertexPositions[i];
			s_RendererData.QuadVertexBufferPtr->color = color;
			s_RendererData.QuadVertexBufferPtr->texCoords = s_TexCoordsLUT[i];
			s_RendererData.QuadVertexBufferPtr->texID = textureIndex;
			s_RendererData.QuadVertexBufferPtr->tilingFactor = tiling_factor;
			s_RendererData.QuadVertexBufferPtr++;
		}

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.stats.QuadCount++;
	}
	//for textures
	static void CreateQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{

		float textureIndex{ 0.0f };

		for (uint32_t i{ 1 }; i < s_RendererData.TextureSlotIndex; i++)
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
	//for subtextures
	static void CreateQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, const glm::vec4& tint, float tiling_factor)
	{

		float textureIndex{ 0.0f };

		for (uint32_t i{ 1 }; i < s_RendererData.TextureSlotIndex; i++)
		{
			if ((*s_RendererData.TextureSlots[i]) == (*subTexture->GetTexture()))
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = static_cast<float>(s_RendererData.TextureSlotIndex);
			s_RendererData.TextureSlots[s_RendererData.TextureSlotIndex] = subTexture->GetTexture();
			s_RendererData.TextureSlotIndex++;
			s_RendererData.TextureSlotIndex = std::clamp(s_RendererData.TextureSlotIndex, 1u, 31u);
		}

		const glm::vec2* texCoords{ subTexture->GetTexCoords() };

		for (int i{}; i < 4; i++)
		{
			s_RendererData.QuadVertexBufferPtr->pos = transform * s_RendererData.QuadVertexPositions[i];
			s_RendererData.QuadVertexBufferPtr->color = tint;
			s_RendererData.QuadVertexBufferPtr->texCoords = texCoords[i];
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

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		DARK_PROFILE_FUNCTION();

		glm::mat4 viewProj{ camera.GetProjection() * glm::inverse(transform) };

		s_RendererData.TextureShader->Bind();
		s_RendererData.TextureShader->SetMat4("u_ProjectionView", viewProj);

		s_RendererData.QuadIndexCount = 0;
		s_RendererData.QuadVertexBufferPtr = s_RendererData.QuadVertexBufferBase;

		s_RendererData.TextureSlotIndex = 1;
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

	//transformed quad
	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		CreateQuad(color, transform);
	}

	//transformed quad with texture
	void Renderer2D::DrawQuad(const glm::mat4& transform, Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		CreateQuad(transform, texture, tint, tiling_factor);
	}

	//transformed quad with sub texture
	void Renderer2D::DrawQuad(const glm::mat4& transform, Ref<SubTexture2D>& subTexture, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}


		CreateQuad(transform, subTexture, tint, tiling_factor);
	}

	//colored quad
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DARK_PROFILE_FUNCTION();

		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount) 
		{
			FlushAndReset();
		}
		
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, position)
				* glm::scale(glm::mat4{1.0f}, glm::vec3{size.x, size.y, 1.0f})
		};

		CreateQuad(color, transform);

	}

	//colored rotated quad
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float angleInRads)
	{

		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, color, angleInRads);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float angleInRads)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, position)
				* glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
					* glm::scale(glm::mat4{1.0f}, glm::vec3{size.x, size.y, 1.0f})
		};

		CreateQuad(color, transform);

	}

	//textured quad
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{

		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tint, tiling_factor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}


		//Setting Vertex Stuff;
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, position)
				* glm::scale(glm::mat4{1.0f}, glm::vec3{size.x, size.y, 1.0f})
		};

		CreateQuad(transform, texture, tint, tiling_factor);

	}

	//textured rotated quad
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, texture, angleInRads, tint, tiling_factor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		//Setting Vertex Stuff;
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, position)
				* glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f}) 
					* glm::scale(glm::mat4{1.0f}, glm::vec3{size.x, size.y, 1.0f})
		};

		CreateQuad(transform, texture, tint, tiling_factor);

	}

	//sub textured Quad
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& tint, float tiling_factor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, subTexture, tint, tiling_factor);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		//Setting Vertex Stuff;
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, position)
				* glm::scale(glm::mat4{1.0f}, glm::vec3{size.x, size.y, 1.0f})
		};

		CreateQuad(transform, subTexture, tint, tiling_factor);

	}

	//rotated sub textured quad
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, subTexture, angleInRads, tint, tiling_factor);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float angleInRads, const glm::vec4& tint, float tiling_factor)
	{
		DARK_PROFILE_FUNCTION();

		if (s_RendererData.QuadIndexCount >= Renderer2DData::MaxIndexCount)
		{
			FlushAndReset();
		}

		//Setting Vertex Stuff;
		glm::mat4 transform{
			glm::translate(glm::mat4{1.0f}, position)
				* glm::rotate(glm::mat4{1.0f}, angleInRads, glm::vec3{0.0f, 0.0f, 1.0f})
					* glm::scale(glm::mat4{1.0f}, glm::vec3{size.x, size.y, 1.0f})
		};

		CreateQuad(transform, subTexture, tint, tiling_factor);

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