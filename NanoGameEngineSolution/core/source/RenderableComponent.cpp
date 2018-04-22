#include"../include/ecs/RenderableComponent.h"



namespace nano { namespace ecs { 

	RenderableComponent::~RenderableComponent()
	{
		delete m_Texture;
	}

	void RenderableComponent::setColor(const math::Vector4 a_Color)
	{
		m_Color = a_Color;
	}

	math::Vector4 RenderableComponent::getColor()
	{
		return m_Color;
	}

	opengl::Texture * RenderableComponent::getTexture()
	{
		return m_Texture;
	}

} }