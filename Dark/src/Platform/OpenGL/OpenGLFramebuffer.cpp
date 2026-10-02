#include "dpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Dark
{

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecifications& spec)
		: m_Specifications{ spec }
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthStencilAttachment);
		glDeleteFramebuffers(1, &m_RendererID);
	}

	//Re creating the frame buffer
	void OpenGLFramebuffer::Invalidate()
	{

		if (m_RendererID)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

			glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specifications.Width, m_Specifications.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			glBindTexture(GL_TEXTURE_2D, m_DepthStencilAttachment);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specifications.Width, m_Specifications.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

			DARK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is Incomplete or invalid!");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		else {
			glCreateFramebuffers(1, &m_RendererID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

			glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
			glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specifications.Width, m_Specifications.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			//attaching the color texture attachment to the framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

			//depth stencil attachments
			glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthStencilAttachment);
			glBindTexture(GL_TEXTURE_2D, m_DepthStencilAttachment);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specifications.Width, m_Specifications.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

			//attaching the depthstenctil attachment to the framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthStencilAttachment, 0);

			DARK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is Incomplete or invalid!");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specifications.Width, m_Specifications.Height);
	}

	void OpenGLFramebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::ReSize(uint32_t _width, uint32_t _height)
	{
		m_Specifications.Width = _width;
		m_Specifications.Height = _height;

		//reinvalidate it
		Invalidate();
	}

	const std::pair<uint32_t, uint32_t>& OpenGLFramebuffer::GetSize() const
	{
		return { m_Specifications.Width, m_Specifications.Height };
	}

}