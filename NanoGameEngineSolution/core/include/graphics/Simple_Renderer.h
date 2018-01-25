#pragma once

#include<deque>
#include"../opengl/NanoOpenGL.h"
#include"Vertex.h"

#define MAX_PRIMITIVES 500
#define VERTEX_SIZE sizeof(nano::graphics::Vertex)

#define TRIANGLE_SIZE 3*VERTEX_SIZE
#define TRIANGLE_BUFFER_SIZE TRIANGLE_SIZE * MAX_PRIMITIVES

#define QUAD_SIZE 4*VERTEX_SIZE
#define QUAD_BUFFER_SIZE QUAD_SIZE * MAX_PRIMITIVES
#define INDICES_COUNT MAX_PRIMITIVES*6

namespace nano { namespace graphics { 

	class Renderable;
	class Shader;
	class OrthographicCamera;

	class SimpleRenderer {
	private:
		opengl::VertexBuffer *m_triangleVBO, *m_quadVBO;
		opengl::VertexArrayObject *m_triangleVAO, *m_quadVAO;
		opengl::IndexBuffer *m_quadIBO;
		Shader *m_shader;

		int m_triangleCount, m_quadCount;

	public:
		OrthographicCamera *m_camera;
		// Default Constructor
		SimpleRenderer();

		// Destructor
		~SimpleRenderer();

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

		//////////
		// \brief Returns the render camera
		//
		OrthographicCamera *GetCamera();
	};

} } 