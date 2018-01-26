#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"

// FWD
namespace nano {
	class CoreConfig;
	namespace editor {
		class WorldSystem;
		class InputSystem;
	}
	namespace ecs {
		class Entity;
	}
	namespace math {
		class Vector2;
	}
}


namespace nano { namespace editor {  

	class EntitySelectWidget : EditorWidget, public EventObserver {
	private:
		CoreConfig* m_config;
		WorldSystem* m_entityManager;
		InputSystem* m_inputSystem;
		ecs::Entity *m_leftClickedEntity;

		// Private methods
		bool IsMouseInViewFrustrum(const math::Vector2& a_pos);

	public:
		EntitySelectWidget();

		// Base class 
		void Start() override;
		void Update() override;
		void Render() override;
	};
	
} }