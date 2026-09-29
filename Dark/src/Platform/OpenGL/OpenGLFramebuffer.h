#pragma once

#include "Dark/Renderer/Framebuffer.h"

namespace Dark
{

	class OpenGLFramebuffer : public Framebuffer
	{

	private:
		FramebufferSpecifications m_Specifications;
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthStencilAttachment;

	public:
		OpenGLFramebuffer(const FramebufferSpecifications& spec);
		virtual ~OpenGLFramebuffer();

		//Re creating the framebuffer cuz its not valid or smt
		void Invalidate();

		//temporary, binding a framebuffer should be the job for the renderer
		virtual void Bind() override;
		virtual void UnBind() override;

		inline virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

		inline virtual const FramebufferSpecifications& GetSpecifications() const override { return m_Specifications; }
		inline virtual FramebufferSpecifications& GetSpecifications() override { return m_Specifications; }
	};

}