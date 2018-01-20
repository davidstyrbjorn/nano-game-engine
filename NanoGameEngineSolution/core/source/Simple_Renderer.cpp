#include"../include/graphics/Simple_Renderer.h"

#include"../include/graphics/Renderable.h"

#define GLEW_STATIC
#include"GL\glew.h"

#include<cassert>

namespace nano { namespace graphics {

	SimpleRenderer::SimpleRenderer()
	{
		// Triangle
		m_triangleVAO = new opengl::VertexArrayObject();
		m_triangleVAO->Bind();

		m_triangleVBO = new opengl::VertexBuffer(nullptr, TRIANGLE_BUFFER_SIZE, GL_DYNAMIC_DRAW);
		m_triangleVBO->Bind();

		m_triangleVAO->EnableVertexAttribArray(0);
		m_triangleVAO->EnableVertexAttribArray(1);
		m_triangleVAO->SetVertexAttribPointer(0, 2, GL_FLOAT, sizeof(Vertex), 0);
		m_triangleVAO->SetVertexAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_COLOR);
		m_triangleVAO->Unbind();

		// Quad
		m_quadVAO = new opengl::VertexArrayObject();
		m_quadVAO->Bind();
		
		m_quadVBO = new opengl::VertexBuffer(nullptr, QUAD_BUFFER_SIZE, GL_DYNAMIC_DRAW);
		m_quadVBO->Bind();
		
		m_quadVAO->EnableVertexAttribArray(0);
		m_quadVAO->EnableVertexAttribArray(1);
		m_quadVAO->SetVertexAttribPointer(0, 2, GL_FLOAT, sizeof(Vertex), 0);
		m_quadVAO->SetVertexAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_COLOR);
		
		int m_indicesOffset = 0;
		GLuint m_indices[INDICES_COUNT];
		for (int i = 0; i < INDICES_COUNT; i += 6)
		{
			m_indices[i + 0] = m_indicesOffset + 0;
			m_indices[i + 1] = m_indicesOffset + 1;
			m_indices[i + 2] = m_indicesOffset + 2;
		
			m_indices[i + 3] = m_indicesOffset + 2;
			m_indices[i + 4] = m_indicesOffset + 3;
			m_indices[i + 5] = m_indicesOffset + 0;
		
			m_indicesOffset += 4;
		}
		m_quadIBO = new opengl::IndexBuffer(m_indices, sizeof(m_indices));
		
		m_quadVAO->Unbind();
	}

	void SimpleRenderer::Begin()
	{
		m_triangleCount = 0;
		m_triangleVBO->Bind();
		m_triangleVBO->SetData(nullptr, TRIANGLE_BUFFER_SIZE, GL_DYNAMIC_DRAW);

		m_quadCount = 0;
		m_quadVBO->Bind();
		m_quadVBO->SetData(nullptr, QUAD_BUFFER_SIZE, GL_DYNAMIC_DRAW);
	}

	void SimpleRenderer::Submit(Renderable * a_renderable)
	{
		assert(a_renderable->GetVertexCount() != -1 || (m_quadCount + m_triangleCount) < MAX_PRIMITIVES); // Invalid argument or we've passed primitive threshold!

		if (a_renderable->GetVertexCount() == 3) {
			// Triangle
			GLintptr _offset = m_triangleCount * (TRIANGLE_SIZE);

			math::Vector2 pos = a_renderable->GetTransformComponent()->position;
			math::Vector2 size = a_renderable->GetSize();
			math::Vector4 color = a_renderable->GetColor();

			Vertex data[] = {
				{ math::Vector2(pos.x,pos.y), color },
				{ math::Vector2(pos.x, pos.y + size.y), color },
				{ pos+size, color }
			};

			m_triangleVBO->Bind();
			m_triangleVBO->SetDatSub(_offset, sizeof(data), (float*)&data);
			m_triangleVBO->Unbind();

			m_triangleCount++;
		}
		else if (a_renderable->GetVertexCount() == 4) {
			// Quad
			GLintptr _offset = m_quadCount * (QUAD_SIZE);

			math::Vector2 pos = a_renderable->GetTransformComponent()->position;
			math::Vector2 size = a_renderable->GetSize();
			math::Vector4 color = a_renderable->GetColor();

			Vertex data[] = {
				{ math::Vector2(pos.x,pos.y), color },
				{ math::Vector2(pos.x, pos.y + size.y), color },
				{ pos + size, color },
				{ math::Vector2(pos.x + size.x, pos.y), color },
			};

			m_quadVBO->Bind();
			m_quadVBO->SetDatSub(_offset, sizeof(data), (float*)&data);
			m_quadVBO->Unbind();

			m_quadCount++;
		}
	}

	void SimpleRenderer::Flush()
	{
		if (m_triangleCount != 0) {
			m_triangleVAO->Bind();
			m_triangleVBO->Bind();

			glDrawArrays(GL_TRIANGLES, 0, m_triangleCount * 3);

			m_triangleVAO->Unbind();
			m_triangleVBO->Unbind();
		}
		if (m_quadCount != 0) {
			m_quadVAO->Bind();
			m_quadIBO->Bind();
			m_quadVAO->Bind();

			glDrawElements(GL_TRIANGLES, 6 * m_quadCount, GL_UNSIGNED_INT, nullptr);

			m_quadVAO->Unbind();
			m_quadIBO->Unbind();
			m_quadVBO->Unbind();
		}
	}
	
} }