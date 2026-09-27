#include "dpch.h"
#include "SubTexture.h"

namespace Dark
{

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& minBound, const glm::vec2& maxBound)
		: m_Texture(texture),
		m_TexCoords
		{
			{minBound.x, minBound.y},
			{maxBound.x, minBound.y},
			{maxBound.x, maxBound.y},
			{minBound.x, maxBound.y}
		}

	{
		//m_TexCoords[0] = { minBound.x, minBound.y };
		//m_TexCoords[1] = { maxBound.x, minBound.y };
		//m_TexCoords[2] = { maxBound.x, maxBound.y };
		//m_TexCoords[3] = { minBound.x, maxBound.y };

	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{

		glm::vec2 minBound{ (coords.x * cellSize.x) / (float)texture->GetWidth(), (coords.y * cellSize.y) / (float)texture->GetHeight() };
		glm::vec2 maxBound{ ((coords.x + spriteSize.x) * cellSize.x) / (float)texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / (float)texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, minBound, maxBound);

	}

}
