#include"../include/opengl/VertexArrayObject.h"

#define GLEW_STATIC
#include<GL\glew.h>

namespace nano { namespace opengl {

	VertexArrayObject::VertexArrayObject()
	{
		glGenVertexArrays(1, &m_vertexArrayObject);
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &m_vertexArrayObject);
	}

	void VertexArrayObject::EnableVertexAttribArray(int a_index)
	{
		glEnableVertexAttribArray(a_index);
	}

	void VertexArrayObject::SetVertexAttribPointer(int a_index, int a_count, GLenum a_type, GLsizei a_internalStride, const void * a_pointer)
	{
		glVertexAttribPointer(a_index, a_count, a_type, false, a_internalStride, a_pointer);
	}

	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_vertexArrayObject);
	}

	void VertexArrayObject::Unbind()
	{
		glBindVertexArray(0);
	}
	
} }