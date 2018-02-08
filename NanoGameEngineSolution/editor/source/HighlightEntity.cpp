#include"../include/HighlightEntity.h"

#include<ecs\components\SpriteComponent.h>
#include<ecs\components\TransformComponent.h>

namespace nano { namespace editor {  

	HighlightEntity::HighlightEntity()
	{
		m_thisEntity = new ecs::Entity("entity");
		m_thisEntity->Start();

		m_thisEntity->AddComponent(new ecs::SpriteComponent("D:\\temp\\rect.png"));
		m_thisRenderable = m_thisEntity->GetRenderableComponent();
	}

	HighlightEntity::~HighlightEntity()
	{
		delete m_thisEntity; // Private pointer for this class
	}

	void HighlightEntity::Update()
	{
		if (m_entityToHighlight != nullptr) 
		{
			m_thisEntity->m_transform->size = m_entityToHighlight->m_transform->size;
			m_thisEntity->m_transform->position = m_entityToHighlight->m_transform->position;
		}
	}

	void HighlightEntity::SetNewHighlightedEntity(ecs::Entity * a_entity)
	{
		m_entityToHighlight = a_entity;
	}

	graphics::Renderable * HighlightEntity::GetRenderable()
	{
		return m_thisRenderable;
	}

	bool HighlightEntity::ShouldHighlight() const
	{
		return m_entityToHighlight != nullptr ? true : false;
	}

} }