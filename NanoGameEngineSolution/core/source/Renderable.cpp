#include"../include/graphics/Renderable.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace graphics {

	void Renderable::SetColor(const math::Vector4 a_color)
	{
		m_color = a_color;
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