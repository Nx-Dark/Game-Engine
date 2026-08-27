#pragma once

#include "Dark/Renderer/Texture.h"

namespace Dark {

	class OpenGLTexture2D : public Texture2D
	{

		uint32_t m_RendererID{};
		uint32_t m_Width{}, m_Height{};
		uint32_t m_Bpp{};
		uint32_t m_InternalFormat, m_DataFormat{};

		std::string m_Path{};

	public:
		OpenGLTexture2D(const std::string& filePath);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint8_t t_Slot = 0) const override;
		virtual void UnBind() const override;

	};

}