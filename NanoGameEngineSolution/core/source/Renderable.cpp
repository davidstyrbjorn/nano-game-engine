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

	void Renderable::SetSize(const math::Vector2 a_size)
	{
		m_size = a_size;
	}

	void Renderable::SetColor(const math::Vector4 a_color)
	{
		m_color = a_color;
	}

	math::Vector2 Renderable::GetSize()
	{
		return m_size;
	}

	math::Vector4 Renderable::GetColor()
	{
		return m_color;
	}

	ecs::Transform * Renderable::GetTransformComponent()
	{
		return m_transform;
	}

	int Renderable::GetVertexCount()
	{
		return -1;
	}
	
} }