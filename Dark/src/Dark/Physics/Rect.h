#pragma once

#include <glm/glm.hpp>

namespace Dark {

	struct Rect
	{
		glm::vec2 position{};
		glm::vec2 size{};

		Rect(const glm::vec2& _pos = glm::vec2{0.0f}, const glm::vec2& _size = glm::vec2{1.0f});
	};

	struct ColorRect
	{
		glm::vec2 position{};
		glm::vec2 size{};
		glm::vec4 color{};

		ColorRect(const glm::vec2& _pos = glm::vec2{0.0f}, const glm::vec2& _size = glm::vec2{1.0f}, const glm::vec4& _color = glm::vec4{1.0f});
	};

}