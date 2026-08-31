#include "dpch.h"
#include "Rect.h"

namespace Dark {

	Rect::Rect(const glm::vec2& _pos, const glm::vec2& _size)
		: position{ _pos }, size{ _size }
	{
	}

	ColorRect::ColorRect(const glm::vec2& _pos, const glm::vec2& _size, const glm::vec4& _color)
		: position{_pos}, size{_size}, color{_color}
	{
	}
}