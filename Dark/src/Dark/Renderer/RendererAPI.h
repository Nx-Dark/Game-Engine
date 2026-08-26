#pragma once

#include <glm/glm.hpp>

#include "Dark/Renderer/VertexArray.h"

namespace Dark {

	class RendererAPI
	{

	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			Direct3D = 2,
			Vulkan = 3,
			Metal = 4
		};

	private:

		static API s_API;

	public:
		virtual void Init() = 0;

		virtual void SetViewport(int x, int y, int w, int h) = 0;

		virtual void Clear(const glm::vec4& p_Color) = 0;
		
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
		inline static void SetAPI(API api) { s_API = api; }
	};

}