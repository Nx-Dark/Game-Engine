#include "dpch.h"
#include "VertexArray.h"

#include "Dark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Dark {

	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "Rendering API NONE, Error!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		DARK_CORE_ASSERT(false, "Unknown Rendering API, ERROR!");
		return nullptr;
	}

}