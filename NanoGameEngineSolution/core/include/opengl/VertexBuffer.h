#pragma once

#include"NanoOpenGLBase.h"
#include"../Core.h"

namespace nano { namespace opengl { 

	class VertexBuffer : public OpenGLBase {
	private:
		GLuint m_verteBufferObject;

	public:
		// Creates a VBO with no set data
		VertexBuffer();

		// Creates VBO and fills it with a_data
		VertexBuffer(float* a_data, size_t a_dataSize, GLenum a_drawMode);
		
		// Deletes the VBO
		~VertexBuffer();
		
		// Sets the VBO's buffer data
		void SetData(float* a_data, size_t a_dataSize, GLenum a_drawMode);

		// Sets a section of the buffers data
		void SetDatSub(GLintptr a_offset, GLsizei a_size, float *a_data);

		// Binds index buffer
		void Bind() override;
		
		// Unbinds index buffer
		void Unbind() override;
	};

} } 
