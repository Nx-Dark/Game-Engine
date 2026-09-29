#pragma once

#include "Dark/Core/Core.h"

namespace Dark
{

	struct FramebufferSpecifications
	{
		uint32_t Width{ 960 }, Height{ 540 };
		uint32_t Samples{ 1 };
		bool SwapChainTarget{};
	};

	class DARK_API Framebuffer
	{
	private:


	public:

		~Framebuffer() {}

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecifications& GetSpecifications() const = 0;
		virtual FramebufferSpecifications& GetSpecifications() = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecifications& spec = FramebufferSpecifications{});
	};

}