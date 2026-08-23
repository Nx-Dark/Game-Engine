#include "dpch.h"
#include "OpenGLTexture.h"

#include "glad/glad.h"

#include "stb_image.h"

namespace Dark {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath)
		: m_Path(filePath)
	{

		//loading image to memory
		int width{}, height{}, channels{};
		stbi_set_flip_vertically_on_load(true);
		stbi_uc_ptr img_data{ stbi_load(m_Path.c_str(), &width, &height, &channels, 0) };
		DARK_CORE_ASSERT(img_data, "Failed to Load Image!");
		m_Width = width; m_Height = height;

		GLenum internalFormat{0}, dataFormat{0};

		switch (channels) {
			case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
			case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
		}
		
		DARK_CORE_ASSERT(internalFormat & dataFormat, "Texture Image Format Not Supported!");

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


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint8_t t_Slot) const
	{
		glBindTextureUnit(t_Slot, m_RendererID);
	}

	void OpenGLTexture2D::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}