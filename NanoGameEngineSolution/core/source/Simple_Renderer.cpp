#include"../include/graphics/Simple_Renderer.h"

#include"../include/graphics/Renderable.h"

#define GLEW_STATIC
#include"GL\glew.h"

namespace nano { namespace graphics {

	SimpleRenderer::SimpleRenderer()
	{
		m_triangleVAO = new opengl::VertexArrayObject();
		m_triangleVAO->Bind();

		m_triangleVBO = new opengl::VertexBuffer(nullptr, TRIANGLE_BUFFER_SIZE, GL_DYNAMIC_DRAW);

		m_triangleVAO->EnableVertexAttribArray(0);
		m_triangleVAO->EnableVertexAttribArray(1);
		m_triangleVAO->SetVertexAttribPointer(0, 2, GL_FLOAT, sizeof(Vertex), 0);
		m_triangleVAO->SetVertexAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_COLOR);

		m_triangleVAO->Unbind();
	}

	void SimpleRenderer::Begin()
	{
		m_triangleCount = 0;
		m_triangleVBO->SetData(nullptr, TRIANGLE_BUFFER_SIZE, GL_DYNAMIC_DRAW);
	}

	void SimpleRenderer::Submit(Renderable * a_renderable)
	{
		if (a_renderable->GetVertexCount() == -1) {
			std::cout << "Invalid vertex count" << std::endl;
			return;
		}
		else if (a_renderable->GetVertexCount() == 3) {
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
	}
	
} }