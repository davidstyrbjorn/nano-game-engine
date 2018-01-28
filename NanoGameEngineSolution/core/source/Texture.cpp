#include"../include/opengl/Texture.h"

#define GLEW_STATIC
#include<GL\glew.h>

namespace nano { namespace opengl { 

	Texture::Texture(unsigned char* a_imageData, unsigned int a_width, unsigned int a_height)
	{
		glGenTextures(1, &m_textureID);
		this->Bind();
		
		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		// Fill the texture buffer with the image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, a_width, a_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_imageData);

		glActiveTexture(GL_TEXTURE0);

		this->Unbind();
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureID);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} }