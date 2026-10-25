#pragma once

#include "Dark/Core/Core.h"

#include <glm/vec2.hpp>

namespace Dark
{

	enum class FramebufferTextureFormat
	{
		None = 0,

		//Color
		RGBA8,

		//Depth
		DEPTH24STENCIL8,

		//Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecifications
	{
		FramebufferTextureSpecifications() = default;
		FramebufferTextureSpecifications(FramebufferTextureFormat format)
			: TextureFormat{format} {}

		FramebufferTextureFormat TextureFormat{ FramebufferTextureFormat::None };
		//TODO: Filtering and Wrap
	};

	struct FramebufferAttachmentSpecifications
	{
		FramebufferAttachmentSpecifications() = default;
		FramebufferAttachmentSpecifications(std::initializer_list<FramebufferTextureSpecifications> attachments)
			: Attachments{attachments} { }

		std::vector<FramebufferTextureSpecifications> Attachments{};
	};

	struct FramebufferSpecifications
	{
		uint32_t Width{ 960 }, Height{ 540 };
		FramebufferAttachmentSpecifications Attachments{};
		uint32_t Samples{ 1 }; //for multi sampling
		bool SwapChainTarget{};
	};

	class DARK_API Framebuffer
	{
	private:


	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void ReSize(uint32_t _width, uint32_t _height) = 0;
		virtual const std::pair<uint32_t, uint32_t> GetSize() const = 0;
		virtual uint32_t GetSizeX() const = 0;
		virtual uint32_t GetSizeY() const = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual const FramebufferSpecifications& GetSpecifications() const = 0;
		virtual FramebufferSpecifications& GetSpecifications() = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecifications& spec = FramebufferSpecifications{});
	};

}