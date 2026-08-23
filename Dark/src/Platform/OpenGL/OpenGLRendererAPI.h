#pragma once

#include "Dark/Renderer/RendererAPI.h"

#include <glad/glad.h>

namespace Dark {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear(const glm::vec4& p_Color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};

}