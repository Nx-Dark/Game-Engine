#pragma once

#include "Dark/Renderer/RendererAPI.h"

namespace Dark {

	class RenderCommand
	{
		static RendererAPI* s_RendererAPI;

	public:

		static void Init();

		static void Clear(const glm::vec4& p_Color);

		static void DrawIndexed(const Ref<VertexArray>& vertexArray);
	};

}