#pragma once

#include<ecs\Entity.h>
#include<ecs\RenderableComponent.h>

namespace nano { namespace editor { 

	class HighlightEntity {
	private:
		ecs::Entity* m_entityToHighlight;
		ecs::Entity* m_thisEntity;
		ecs::RenderableComponent* m_thisRenderable;

	public:
		HighlightEntity();
		~HighlightEntity();

		void Update();
		void SetNewHighlightedEntity(ecs::Entity* a_entity);
		ecs::RenderableComponent* GetRenderable();

		bool ShouldHighlight() const;
	};

} }