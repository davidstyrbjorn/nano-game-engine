#pragma once

#include<ecs\Entity.h>
#include<graphics\Renderable.h>

namespace nano { namespace editor { 

	class HighlightEntity {
	private:
		ecs::Entity* m_entityToHighlight;
		ecs::Entity* m_thisEntity;
		graphics::Renderable* m_thisRenderable;

	public:
		HighlightEntity();
		~HighlightEntity();

		void Update();
		void SetNewHighlightedEntity(ecs::Entity* a_entity);
		graphics::Renderable* GetRenderable();

		bool ShouldHighlight() const;
	};

} }