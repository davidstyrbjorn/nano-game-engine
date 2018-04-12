#include"../include/graphics/Simple_Renderer.h"

#include"../include/graphics/Renderable.h"
#include"../include/graphics/Shader.h"
#include"../include/math/Matrix4x4.h"
#include"../include/graphics/Camera.h"
#include"../include/ecs/components/TransformComponent.h"

#define GLEW_STATIC
#include"GL\glew.h"

#include<cassert>

namespace nano { namespace graphics {

	SimpleRenderer::SimpleRenderer(const char* a_vertexPath, const char* a_fragmentPath, const math::Vector2& a_windowSize)
	{
		// Initalize GLEW
		glewInit();

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Create shader
		m_shader = new Shader(a_vertexPath, a_fragmentPath); 
		m_shader->Bind();
		m_shader->SetUniform1f("textureSampler", 0); // GL_TEXTURE0

		m_camera = new OrthographicCamera(a_windowSize);
		m_shader->SetUniformMat4f("projection_matrix", m_camera->GetProjectionMatrix());

		// Triangle
		m_triangleVAO = new opengl::VertexArrayObject();
		m_triangleVAO->Bind();

		m_triangleVBO = new opengl::VertexBuffer(nullptr, TRIANGLE_BUFFER_SIZE, GL_DYNAMIC_DRAW);
		m_triangleVBO->Bind();

		m_triangleVAO->EnableVertexAttribArray(0);  // pos
		m_triangleVAO->EnableVertexAttribArray(1);  // color
		m_triangleVAO->EnableVertexAttribArray(2);  // uv
		m_triangleVAO->SetVertexAttribPointer(0, 2, GL_FLOAT, sizeof(Vertex), 0);
		m_triangleVAO->SetVertexAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_COLOR);
		m_triangleVAO->SetVertexAttribPointer(2, 2, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_UV);

		m_triangleVBO->Unbind();
		m_triangleVAO->Unbind();

		// Quad
		m_quadVAO = new opengl::VertexArrayObject();
		m_quadVAO->Bind();
		
		m_quadVBO = new opengl::VertexBuffer(nullptr, QUAD_BUFFER_SIZE + GRID_BUFFER_SIZE, GL_DYNAMIC_DRAW);
		m_quadVBO->Bind();
		
		m_quadVAO->EnableVertexAttribArray(0);  // pos
		m_quadVAO->EnableVertexAttribArray(1);  // color
		m_quadVAO->EnableVertexAttribArray(2);  // uv
		m_quadVAO->SetVertexAttribPointer(0, 2, GL_FLOAT, sizeof(Vertex), 0);
		m_quadVAO->SetVertexAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_COLOR);
		m_quadVAO->SetVertexAttribPointer(2, 2, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_UV);
		
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
		
		m_quadVBO->Unbind();
		m_quadVAO->Unbind();

		// Texture
		m_textureVAO = new opengl::VertexArrayObject();
		m_textureVAO->Bind();

		m_textureVBO = new opengl::VertexBuffer(nullptr, VERTEX_SIZE * 4, GL_STATIC_DRAW);
		m_textureVBO->Bind();

		m_textureVAO->EnableVertexAttribArray(0);  // pos
		m_textureVAO->EnableVertexAttribArray(1);  // color
		m_textureVAO->EnableVertexAttribArray(2);  // uv
		m_textureVAO->SetVertexAttribPointer(0, 2, GL_FLOAT, sizeof(Vertex), 0);
		m_textureVAO->SetVertexAttribPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_COLOR);
		m_textureVAO->SetVertexAttribPointer(2, 2, GL_FLOAT, sizeof(Vertex), (void*)OFFSET_TO_UV);

		GLuint iboData[] = { 0,1,2,2,3,0 };
		m_textureIBO = new opengl::IndexBuffer(iboData, sizeof(iboData));

		m_textureVBO->Unbind();
		m_textureVAO->Unbind();

	}

	SimpleRenderer::~SimpleRenderer()
	{
		delete m_quadIBO;
		delete m_quadVBO;
		delete m_quadVAO;

		delete m_triangleVBO;
		delete m_triangleVAO;

		delete m_shader;
	}

	void SimpleRenderer::Begin()
	{
		m_triangleCount = 0;
		m_triangleVBO->Bind();
		m_triangleVBO->SetData(nullptr, TRIANGLE_BUFFER_SIZE, GL_DYNAMIC_DRAW);

		m_quadCount = 0;
		m_quadVBO->Bind();
		m_quadVBO->SetData(nullptr, QUAD_BUFFER_SIZE + GRID_BUFFER_SIZE, GL_DYNAMIC_DRAW);
	}

	void SimpleRenderer::Submit(Renderable * a_renderable)
	{
		assert(a_renderable != nullptr); // nullptr to in-argument!
		assert(a_renderable->GetVertexCount() != -1 || (m_quadCount + m_triangleCount) < MAX_PRIMITIVES); // Invalid argument or we've passed primitive threshold!
		
		if (a_renderable->GetVertexCount() == 3) {
			// Triangle
			GLintptr _offset = m_triangleCount * (TRIANGLE_SIZE);
		
			math::Vector2 pos = a_renderable->GetTransformComponent()->position;
			math::Vector2 size = a_renderable->GetTransformComponent()->size;
			math::Vector4 color = a_renderable->GetColor();
		
			Vertex data[] = {
				{ math::Vector2(pos.x,pos.y), color, math::Vector2(-1,-1) },
				{ math::Vector2(pos.x, pos.y + size.y), color, math::Vector2(-1,-1) },
				{ pos+size, color, math::Vector2(-1,-1) }
			};
		
			m_triangleVAO->Bind();
			m_triangleVBO->Bind();
			m_triangleVBO->SetDatSub(_offset, sizeof(data), (float*)&data);
			m_triangleVBO->Unbind();
			m_triangleVAO->Unbind();
		
			m_triangleCount++;
		}
		else if (a_renderable->GetVertexCount() == 4) {
			if (a_renderable->GetTexture() == nullptr) {
				// Quad
				GLintptr _offset = m_quadCount * (QUAD_SIZE);
				
				math::Vector2 pos = a_renderable->GetTransformComponent()->position;
				math::Vector2 size = a_renderable->GetTransformComponent()->size;
				math::Vector4 color = a_renderable->GetColor();
		
				Vertex data[] = {
					{ math::Vector2(pos.x,pos.y), color, math::Vector2(-1,-1) },
					{ math::Vector2(pos.x, pos.y + size.y), color, math::Vector2(-1,-1) },
					{ pos + size, color, math::Vector2(-1,-1) },
					{ math::Vector2(pos.x + size.x, pos.y), color, math::Vector2(-1,-1) },
				};
		
				m_quadVAO->Bind();
				m_quadVBO->Bind();
				m_quadVBO->SetDatSub(_offset, sizeof(data), (float*)&data);
				m_quadVBO->Unbind();
				m_quadVAO->Unbind();
		
				m_quadCount++;
			}
			else {
				AddTextureToRender(a_renderable);
			}
		}
	}

	void SimpleRenderer::AddTextureToRender(Renderable * a_renderable)
	{
		m_texturesToRender.push_back(a_renderable);
	}

	void SimpleRenderer::Flush()
	{
		m_shader->Bind();
		// Update matrices based on camera position & size
		m_shader->SetUniformMat4f("view_matrix", m_camera->GetViewMatrix());
		m_shader->SetUniformMat4f("projection_matrix", m_camera->GetProjectionMatrix());

		if (m_quadCount != 0) {
			m_quadVAO->Bind();

			m_quadIBO->Bind();
			m_quadVAO->Bind();
		
			glDrawElements(GL_TRIANGLES, 6 * m_quadCount, GL_UNSIGNED_INT, nullptr);
		
			m_quadVAO->Unbind();
			m_quadIBO->Unbind();
			m_quadVBO->Unbind();
		}
		if (m_triangleCount != 0) {
			m_triangleVAO->Bind();
			m_triangleVBO->Bind();

			glDrawArrays(GL_TRIANGLES, 0, m_triangleCount * 3);

			m_triangleVAO->Unbind();
			m_triangleVBO->Unbind();
		}

		this->PostFlush();
		m_shader->Unbind();
	}

	void SimpleRenderer::PostFlush()
	{
		// Render the textures we want to render
		while (!m_texturesToRender.empty()) 
		{
			Renderable* texturedRenderable = m_texturesToRender.front();
		
			math::Vector2 pos = texturedRenderable->GetTransformComponent()->position;
			math::Vector2 size = texturedRenderable->GetTransformComponent()->size;
			math::Vector4 color = texturedRenderable->GetColor();
				
			Vertex data[] = {
				{ math::Vector2(pos.x,pos.y), color, math::Vector2(0, 0) },
				{ math::Vector2(pos.x, pos.y + size.y), color, math::Vector2(0, 1) },
				{ pos + size, color, math::Vector2(1, 1) },
				{ math::Vector2(pos.x + size.x, pos.y), color, math::Vector2(1, 0) },
			};
		
			// Bind
			texturedRenderable->GetTexture()->Bind();
			m_textureVAO->Bind();
			m_textureVBO->Bind();
			m_textureIBO->Bind();
		
			m_textureVBO->SetData((float*)&data, sizeof(data), GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
			// Unbind
			m_textureVAO->Unbind();
			m_textureVBO->Unbind();
			m_textureIBO->Unbind();
			texturedRenderable->GetTexture()->Unbind();
			
			m_texturesToRender.pop_front();
		}
	}

	void SimpleRenderer::SubmitGridData()
	{
		static math::Vector4 color = math::Vector4(0.05, 0.05, 0.05, 0.7);
		static math::Vector2 uv = math::Vector2(-1, -1);
		static float gridThickness = 3;
		static int lineOffset = 30;

		GLintptr _offset = m_quadCount * (QUAD_SIZE);
		std::vector<Vertex> gridDataVector;
		math::Vector2 camPos = m_camera->GetPosition();
		math::Vector2 camSize = m_camera->GetSize();

		for (int y = 0; y < (int)(camSize.y/28); y++) {
			gridDataVector.push_back({ camPos + math::Vector2(0, (y*lineOffset)), color, uv });
			gridDataVector.push_back({ camPos + math::Vector2(0, gridThickness + (y*lineOffset)), color, uv });
			gridDataVector.push_back({ camPos + math::Vector2(camSize.x, gridThickness + (y*lineOffset)), color, uv });
			gridDataVector.push_back({ camPos + math::Vector2(camSize.x, (y*lineOffset)), color, uv });
			m_quadCount++;
		}
		for (int x = 0; x < (int)(camSize.x/30); x++) {
			gridDataVector.push_back({ camPos + math::Vector2((x*lineOffset), 0), color, uv });
			gridDataVector.push_back({ camPos + math::Vector2((x*lineOffset), camSize.y), color, uv });
			gridDataVector.push_back({ camPos + math::Vector2(gridThickness + (x*lineOffset), camSize.y), color, uv });
			gridDataVector.push_back({ camPos + math::Vector2(gridThickness + (x*lineOffset), 0), color, uv });
			m_quadCount++;
		}
		
		static math::Vector4 originColorX = math::Vector4(1, 0, 0, 1);
		static math::Vector4 originColorY = math::Vector4(0, 0, 1, 1);
		// Red X origin axis
		gridDataVector.push_back({math::Vector2(0, 0), originColorX, uv });
		gridDataVector.push_back({math::Vector2(0, camPos.y+camSize.y), originColorX, uv });
		gridDataVector.push_back({math::Vector2(gridThickness, camPos.y+camSize.y), originColorX, uv });
		gridDataVector.push_back({math::Vector2(gridThickness, 0), originColorX, uv });
		m_quadCount++; 
		// Blue Y origin axis
		gridDataVector.push_back({math::Vector2(0, 0), originColorY, uv });
		gridDataVector.push_back({math::Vector2(0, gridThickness), originColorY, uv });
		gridDataVector.push_back({math::Vector2(camPos.x+camSize.x, gridThickness), originColorY, uv });
		gridDataVector.push_back({math::Vector2(camPos.x+camSize.x, 0), originColorY, uv });
		m_quadCount++;

		m_quadVAO->Bind();
		m_quadVBO->Bind();
		m_quadVBO->SetDatSub(_offset, gridDataVector.size() * sizeof(Vertex), (float*)gridDataVector.data());
		m_quadVBO->Unbind();
		m_quadVAO->Unbind();
	}

	OrthographicCamera * SimpleRenderer::GetCamera()
	{
		return m_camera;
	}
	
} }