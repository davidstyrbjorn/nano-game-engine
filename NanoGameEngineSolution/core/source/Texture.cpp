#include"../include/opengl/Texture.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/math/Vector2.h"

namespace nano { namespace opengl { 

	Texture::Texture(void* a_imageData, unsigned int a_width, unsigned int a_height, GLenum a_format)
	{
		glGenTextures(1, &m_textureID);
		this->Bind();
		this->SetTextureData(a_imageData, a_width, a_height, a_format);
		this->Unbind();
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureID);
	}

	void Texture::SetTextureData(void* a_imageData, unsigned int a_width, unsigned int a_height, GLenum a_format)
	{
		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		
		// Fill the texture buffer with the image data
		glTexImage2D(GL_TEXTURE_2D, 0, a_format, a_width, a_height, 0, a_format, GL_UNSIGNED_BYTE, a_imageData);

		// Set member values
		m_width = a_width;
		m_height = a_height;
	}

	GLuint Texture::GetTextureID()
	{
		if(glIsTexture(m_textureID))
			return m_textureID;
		return -1;
	}

	math::Vector2 & Texture::GetTextureSize()
	{
		return math::Vector2(m_width, m_height);
	}

	void Texture::Bind()
	{
		// Bind this texture
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} }