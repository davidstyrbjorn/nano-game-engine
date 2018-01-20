#include "../include/opengl/IndexBuffer.h"

#define GLEW_STATIC
#include<GL\glew.h>

namespace nano { namespace opengl {

IndexBuffer::IndexBuffer(const int* a_data, size_t a_dataSize)
{
	glGenBuffers(1, &m_indexBuffer);
	SetData(a_data, a_dataSize);
}

void IndexBuffer::SetData(const int * a_data, size_t a_dataSize)
{
	this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_dataSize, a_data, GL_STATIC_DRAW);
	this->Unbind();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_indexBuffer);
}

} } 
