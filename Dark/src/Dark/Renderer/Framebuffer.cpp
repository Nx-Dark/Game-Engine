#include "dpch.h"
#include "Framebuffer.h"

#include "Dark/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Dark
{

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecifications& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: DARK_CORE_ASSERT(false, "RendererAPI::None is not currently Supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
		}

		DARK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}