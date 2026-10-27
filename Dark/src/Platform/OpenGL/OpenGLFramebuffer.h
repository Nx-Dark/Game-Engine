#pragma once

#include "Dark/Renderer/Framebuffer.h"

namespace Dark
{

	class OpenGLFramebuffer : public Framebuffer
	{

	private:
		FramebufferSpecifications m_Specifications{};
		uint32_t m_RendererID{};

		//attachments
		std::vector<FramebufferTextureSpecifications> m_ColorAttachmentSpecs{};
		FramebufferTextureSpecifications m_DepthAttachmentSpec{};

		//attachment ids;
		std::vector<uint32_t> m_ColorAttachments{};
		uint32_t m_DepthAttachment{};

	public: 
		OpenGLFramebuffer(const FramebufferSpecifications& spec);
		virtual ~OpenGLFramebuffer();

		//Re creating the framebuffer cuz its not valid or smt
		void Invalidate();

		//temporary, binding a framebuffer should be the job for the renderer
		virtual void Bind() override;
		virtual void UnBind() override;

		virtual void ReSize(uint32_t _width, uint32_t _height) override;
		virtual const std::pair<uint32_t, uint32_t> GetSize() const override;
		inline virtual uint32_t GetSizeX() const override { return m_Specifications.Width; }
		inline virtual uint32_t GetSizeY() const override { return m_Specifications.Height; }

		virtual int ReadPixels(uint32_t attachmentIndex, int _mx, int _my) const override;

		inline virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override 
			{ DARK_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }

		inline virtual const FramebufferSpecifications& GetSpecifications() const override { return m_Specifications; }
		inline virtual FramebufferSpecifications& GetSpecifications() override { return m_Specifications; }
	};

}