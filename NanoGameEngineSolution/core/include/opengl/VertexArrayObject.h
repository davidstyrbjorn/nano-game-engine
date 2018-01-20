#pragma once

#include"NanoOpenGLBase.h"
#include"../Core.h"

namespace nano { namespace opengl {
	
	class VertexArrayObject : public OpenGLBase {
	private:
		GLuint m_vertexArrayObject;

	public:
		// Creates and binds a new VAO
		VertexArrayObject();

		// Deletes VAO
		~VertexArrayObject();

		// glEnableVertexAttribArray
		void EnableVertexAttribArray(int a_index);

		// glVertexAttribPointer
		void SetVertexAttribPointer(int a_index, int a_count, GLenum a_type, GLsizei a_internalStride, const void* a_pointer);
		
		// Binds VAO
		void Bind() override;

		// Unbinds VAO
		void Unbind() override;
	};

}}