#pragma once

#include<deque>
#include"../opengl/NanoOpenGL.h"
#include"Vertex.h"

#define MAX_PRIMITIVES 500
#define VERTEX_SIZE sizeof(nano::graphics::Vertex)

#define TRIANGLE_SIZE 3*VERTEX_SIZE
#define TRIANGLE_BUFFER_SIZE TRIANGLE_SIZE * MAX_PRIMITIVES

namespace nano { namespace graphics { 

	class Renderable;

	class SimpleRenderer {
	private:
		opengl::VertexBuffer *m_triangleVBO;
		opengl::VertexArrayObject *m_triangleVAO;

		int m_triangleCount;

	public:
		// Default Constructor
		SimpleRenderer();

		//////////
		// \brief Called at begining of each render frame
		//
		void Begin();

		//////////
		// \brief Pushes back a_renderable to the render list
		//
		void Submit(Renderable* a_renderable);

		//////////
		// \brief Goes through and renders each primitive inside a_renderableList
		//
		void Flush();
	};

} } 