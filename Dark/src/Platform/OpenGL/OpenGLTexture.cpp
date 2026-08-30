#include "dpch.h"
#include "OpenGLTexture.h"

#include "glad/glad.h"

#include "stb_image.h"

namespace Dark {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath)
		: m_Path(filePath)
	{

		DARK_PROFILE_FUNCTION();

		//loading image to memory
		int width{}, height{}, channels{};
		stbi_set_flip_vertically_on_load(true);
		stbi_uc_ptr img_data{ nullptr };

	{
		DARK_PROFILE_SCOPE("OpenGLTexture2D::OpenGLTexture2D(const std::string&) -> stbi_load")
		img_data = stbi_load(m_Path.c_str(), &width, &height, &channels, 0);
	}

		DARK_CORE_ASSERT(img_data, "Failed to Load Image!");
		m_Width = width; m_Height = height;

		GLenum internalFormat{0}, dataFormat{0};

		switch (channels) {
			case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
			case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
		}
		
		DARK_CORE_ASSERT(internalFormat & dataFormat, "Texture Image Format Not Supported!");

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		//create opengl textures and shit
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		//tex parameters
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//upload img data as texture to gpu
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, img_data);

		//free the img
		stbi_image_free(img_data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width{ width }, m_Height{ height }
	{
		DARK_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		m_Bpp = m_InternalFormat == GL_RGBA8 ? 4 : 3;

		//create opengl textures and shit
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		//tex parameters
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		DARK_PROFILE_FUNCTION();

		DARK_CORE_ASSERT(size == m_Width * m_Height * m_Bpp, "Size of Data Must of Full Texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		DARK_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint8_t t_Slot) const
	{
		DARK_PROFILE_FUNCTION();

		glBindTextureUnit(t_Slot, m_RendererID);
	}

	void OpenGLTexture2D::UnBind() const
	{
		DARK_PROFILE_FUNCTION();

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}