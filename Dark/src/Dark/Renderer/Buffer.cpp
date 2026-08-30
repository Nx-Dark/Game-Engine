#include "dpch.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Dark/Renderer/Renderer.h"

namespace Dark {

	//Vertex Buffer Create fn Implementation
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "RendererAPI::None is not currently Supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>( vertices, size );
		}

		DARK_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	
	//Index Buffer Create fn Implementation
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {

		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "RendererAPI::None is not currently Supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>( indices, size );
		}

		DARK_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}
}