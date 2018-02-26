#pragma once

#include<vector>
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

#define GRID_COUNT 864
#define GRID_BUFFER_SIZE GRID_COUNT * QUAD_SIZE

namespace nano {
	class CoreConfig;
}

namespace nano { namespace graphics { 

	class Renderable;
	class Shader;
	class OrthographicCamera;

	class SimpleRenderer {
	private:
		// For now
		// We are going to render textures slow
		// After the batch of triangles and quads have been rendered 
		// We go through every texture and instance render them
		std::deque<Renderable*> m_texturesToRender;

		opengl::VertexBuffer *m_triangleVBO, *m_quadVBO, *m_textureVBO;
		opengl::VertexArrayObject *m_triangleVAO, *m_quadVAO, *m_textureVAO;
		opengl::IndexBuffer *m_quadIBO, *m_textureIBO;
		Shader *m_shader;

		int m_triangleCount, m_quadCount;

		CoreConfig* m_config;
		OrthographicCamera *m_camera;
		
		// Private methods
		void AddTextureToRender(Renderable* a_renderable);
		void PostFlush();

	public:
		// Default Constructor
		SimpleRenderer();

		// Destructor
		~SimpleRenderer();

		//////////
		// \brief Called at begining of each render frame
		//
		void Begin();

		//////////
		// \brief Submits grid data to the current quad vertex buffer
		//
		void SubmitGridData();

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