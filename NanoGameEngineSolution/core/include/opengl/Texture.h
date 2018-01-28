#pragma once

#include"../Core.h"
#include"NanoOpenGLBase.h"

namespace nano { namespace opengl { 

	class Texture : OpenGLBase {
	private:
		GLuint m_textureID;

	public:
		// Default Constructor
		Texture(unsigned char* a_imageData, unsigned int a_width, unsigned int a_height);

		// Destructor
		~Texture();
	
		// Bind & Unbind
		void Bind() override;
		void Unbind() override;
	};

} }