#include "dpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Dark
{

	static const uint32_t s_MaxFramebufferSize{ 8192 };

	namespace Utils {

		static GLenum TextureTarget(bool multiSampled) 
			{ return multiSampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D; }

		static void CreateTextures(bool multiSampled, uint32_t* outID, uint32_t count)
			{ glCreateTextures(TextureTarget(multiSampled), count, outID); }

		static void BindTextures(bool multiSampled, uint32_t id) 
			{ glBindTexture(TextureTarget(multiSampled), id); }

		static void AttachColorTexture(uint32_t id, uint32_t sampleCount, GLenum internalformat, GLenum externalformat, uint32_t width, uint32_t height, uint32_t index)
		{
			bool multiSampled{ sampleCount > 1 };
			if (multiSampled)
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sampleCount, internalformat, width, height, GL_FALSE);
			else
			{
				glTexImage2D(TextureTarget(multiSampled), 0, internalformat, width, height, 0, externalformat, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			//attaching the color texture attachment to the framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multiSampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, uint32_t sampleCount, GLenum internalformat, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multiSampled{ sampleCount > 1 };
			if (multiSampled)
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sampleCount, internalformat, width, height, GL_FALSE);
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, internalformat, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			//attaching the depth texture attachment to the framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multiSampled), id, 0);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
			}
			return false;
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecifications& spec)
		: m_Specifications{ spec }
	{
		for (auto format : m_Specifications.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(format.TextureFormat))
				m_ColorAttachmentSpecs.emplace_back(format);
			else
				m_DepthAttachmentSpec = format;
		}

		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (!m_ColorAttachments.empty())
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());

		if (m_DepthAttachment) glDeleteTextures(1, &m_DepthAttachment);

		glDeleteFramebuffers(1, &m_RendererID);
	}

	//Re creating the frame buffer
	void OpenGLFramebuffer::Invalidate()
	{

		if (m_RendererID)
		{
			if(!m_ColorAttachments.empty())
				glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());

			if(m_DepthAttachment) glDeleteTextures(1, &m_DepthAttachment);

			glDeleteFramebuffers(1, &m_RendererID);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		//creating and binding a framebuffer object
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multiSample{ m_Specifications.Samples > 1 };

		//Color Attachments stuff
		if (m_ColorAttachmentSpecs.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
			Utils::CreateTextures(multiSample, m_ColorAttachments.data(), m_ColorAttachments.size());

			for (size_t i{}; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTextures(multiSample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecs[i].TextureFormat)
				{
					case FramebufferTextureFormat::RGBA8:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Specifications.Samples, GL_RGBA8, GL_RGBA, m_Specifications.Width, m_Specifications.Height, i);
						break;
					case FramebufferTextureFormat::RED_INTEGER:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Specifications.Samples, GL_R32I, GL_RED_INTEGER, m_Specifications.Width, m_Specifications.Height, i);
						break;

				}
			}
		}

		if (m_DepthAttachmentSpec.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multiSample, &m_DepthAttachment, 1);
			Utils::BindTextures(multiSample, m_DepthAttachment);
			switch (m_DepthAttachmentSpec.TextureFormat)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					Utils::AttachDepthTexture(m_DepthAttachment, m_Specifications.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specifications.Width, m_Specifications.Height);
					break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			//right now, only 6 color attachment per framebuffer object is supported!
			DARK_CORE_ASSERT(m_ColorAttachment.size() <= 6);
			GLenum attachmentBuffers[6]{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5 };
			glDrawBuffers(m_ColorAttachments.size(), attachmentBuffers);
		}
		else if (m_ColorAttachments.empty())
			//only depth pass
			glDrawBuffer(GL_NONE);

		DARK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is Incomplete or invalid!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
		if (_width == 0 || _height == 0 || _width > s_MaxFramebufferSize || _height > s_MaxFramebufferSize) {
			DARK_CORE_ERROR("Attempted to Resize Framebuffer to ({0}, {1})", _width, _height);
			return;
		}

		m_Specifications.Width = _width;
		m_Specifications.Height = _height;

		//reinvalidate it
		Invalidate();
	}

	const std::pair<uint32_t, uint32_t> OpenGLFramebuffer::GetSize() const
	{
		return { m_Specifications.Width, m_Specifications.Height };
	}

	int OpenGLFramebuffer::ReadPixels(uint32_t attachmentIndex, int _mx, int _my) const
	{
		//make sure to bind the framebuffer before callling this func;
		DARK_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelVal{};
		glReadPixels(_mx, _my, 1, 1, GL_RED_INTEGER, GL_INT, &pixelVal);
		return pixelVal;
	}

}