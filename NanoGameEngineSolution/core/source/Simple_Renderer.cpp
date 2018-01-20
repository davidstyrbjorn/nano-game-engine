#include"../include/graphics/Simple_Renderer.h"

#include"../include/graphics/Renderable.h"

namespace nano { namespace graphics {

	void SimpleRenderer::Submit(Renderable * a_renderable)
	{
		m_renderList.push_back(a_renderable);
	}

	void SimpleRenderer::Flush()
	{
		while (!m_renderList.empty()) 
		{
			Renderable* temp = m_renderList.back();

			if (temp->GetVertexCount() == -1) {
				// Invalid primitive
				std::cout << "no stop! vertex method from renderable base class not implemented" << std::endl;
			}
			else if (temp->GetVertexCount() == 3) {
				// Triangle
				std::cout << "Render a triangle" << std::endl;
			}
			else if (temp->GetVertexCount() == 4) {
				// Quad
				std::cout << "Render a quad" << std::endl;
			}

			m_renderList.pop_back();
		}
	}
	
} }