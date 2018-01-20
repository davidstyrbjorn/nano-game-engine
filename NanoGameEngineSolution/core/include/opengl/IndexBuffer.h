#pragma once

#include"../Core.h"
#include"NanoOpenGLBase.h"

namespace nano { namespace opengl { 

	class IndexBuffer : public OpenGLBase {
	private:
		GLuint m_indexBuffer;

	public:
		// Creates the index buffer
		IndexBuffer(const int* a_data, size_t a_dataSize);

		// Deletes the index buffer
		~IndexBuffer();

		// Sets the data of the Index buffer
		void SetData(const int* a_data, size_t a_dataSize);

		// Binds index buffer
		void Bind() override;

		// Unbinds index buffer
		void Unbind() override;
	};

} } 