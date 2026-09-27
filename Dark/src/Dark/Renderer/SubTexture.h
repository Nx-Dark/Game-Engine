#pragma once

#include <glm/glm.hpp>
#include "Dark/Renderer/Texture.h"

namespace Dark
{
	
	class SubTexture2D
	{

		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];

	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& minBound, const glm::vec2& maxBound);

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });

		inline const glm::vec2* GetTexCoords() const { return m_TexCoords; }
		inline const Ref<Texture2D>& GetTexutre() const { return m_Texture; }

	};


}