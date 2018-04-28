#include"../include/graphics/Renderable.h"
#include"../include/ecs/components/TransformComponent.h"

#include"../include/opengl/Texture.h"

namespace nano { namespace graphics {

	Renderable::~Renderable()
	{
		delete m_texture;
	}

	void Renderable::SetColor(const math::Vector4 a_color)
	{
		m_color = a_color;
	}

	void Renderable::SetRenderOrder(const int a_renderOrder)
	{
		m_renderOrder = a_renderOrder;
	}

	math::Vector4 Renderable::GetColor()
	{
		return m_color;
	}

	ecs::Transform * Renderable::GetTransformComponent()
	{
		return m_transform;
	}

	opengl::Texture * Renderable::GetTexture()
	{
		return m_texture;
	}

	int Renderable::GetRenderOrder() const
	{
		return m_renderOrder;
	}

	int Renderable::GetVertexCount()
	{
		return -1;
	}
	
} }