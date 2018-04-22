#include"../include/HighlightEntity.h"

#include<ecs\components\SpriteComponent.h>
#include<ecs\components\TransformComponent.h>

#include"../include/systems/AssetSystem.h"

namespace nano { namespace editor {  

	HighlightEntity::HighlightEntity()
	{
		m_thisEntity = new ecs::Entity("entity");
		m_thisEntity->Start();

		m_thisEntity->AddComponent(ecs::_ComponentTypes::SPRITE_COMPONENT);
		m_thisEntity->Renderable()->LoadAsset((asset::Asset*)AssetSystem::getInstance()->getHighlightAsset());
		m_thisRenderable = m_thisEntity->Renderable();
	}

	HighlightEntity::~HighlightEntity()
	{
		delete m_thisEntity; // Private pointer for this class
	}

	void HighlightEntity::Update()
	{
		if (m_entityToHighlight != nullptr) 
		{
			m_thisEntity->Transform()->size = m_entityToHighlight->Transform()->size;
			m_thisEntity->Transform()->position = m_entityToHighlight->Transform()->position;
		}
	}

	void HighlightEntity::SetNewHighlightedEntity(ecs::Entity * a_entity)
	{
		m_entityToHighlight = a_entity;
	}

	ecs::RenderableComponent * HighlightEntity::GetRenderable()
	{
		return m_thisRenderable;
	}

	bool HighlightEntity::ShouldHighlight() const
	{
		return m_entityToHighlight != nullptr ? true : false;
	}

} }