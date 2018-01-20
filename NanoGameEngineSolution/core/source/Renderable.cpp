#include"../include/graphics/Renderable.h"

namespace nano { namespace graphics {

	Renderable::Renderable()
	{
		m_size = math::Vector2(0, 0);
		m_color = math::Vector4(0, 0, 0, 0);
	}

	Renderable::Renderable(const math::Vector2 & a_size, const math::Vector4 & a_color)
	{
		m_size = a_size;
		m_color = a_color;
	}
	
} }