#include "dpch.h"
#include "Texture.h"

#include "Dark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Dark {

	Ref<Texture2D> Texture2D::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "Rendering API NONE, Error!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(filePath);

		}

		DARK_CORE_ASSERT(false, "UnKnown Rendering API, Error!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: DARK_CORE_ASSERT(false, "Rendering API NONE, Error!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);

		}

		DARK_CORE_ASSERT(false, "UnKnown Rendering API, Error!");
		return nullptr;
	}

}