#pragma once

#include"../Core.h"
#include"NanoOpenGLBase.h"

namespace nano {
	namespace math {
		class Vector2;
	}
}

namespace nano { namespace opengl { 

	class Texture : OpenGLBase {
	private:
		GLuint m_textureID;
		unsigned int m_width, m_height;
		unsigned int m_textureSlot;

	public:
		// Default Constructor
		Texture(void* a_imageData, unsigned int a_width, unsigned int a_height, GLenum a_format);

		// Destructor
		~Texture();

		// Other
		void SetTextureData(void* a_imageData, unsigned int a_width, unsigned int a_height, GLenum a_format);

		// Getters
		GLuint GetTextureID();
		math::Vector2& GetTextureSize();
	
		// Bind & Unbind
		void Bind() override;
		void Unbind() override;
	};

} }