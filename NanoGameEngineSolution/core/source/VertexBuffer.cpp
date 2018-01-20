#include"../include/opengl/VertexBuffer.h"

#define GLEW_STATIC
#include<GL\glew.h>

namespace nano { namespace opengl {

	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_verteBufferObject);
	}

	VertexBuffer::VertexBuffer(float * a_data, size_t a_dataSize, GLenum a_drawMode)
	{
		glGenBuffers(1, &m_verteBufferObject);
		SetData(a_data, a_dataSize, a_drawMode);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_verteBufferObject);
	}

	void VertexBuffer::SetData(float * a_data, size_t a_dataSize, GLenum a_drawMode)
	{
		this->Bind();
		glBufferData(GL_ARRAY_BUFFER, a_dataSize, a_data, a_drawMode);
		this->Unbind();
	}

	void VertexBuffer::SetDatSub(GLintptr a_offset, GLsizei a_size, float * a_data)
	{
		this->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, a_offset, a_size, a_data);
		this->Unbind();
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_verteBufferObject);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

} } 