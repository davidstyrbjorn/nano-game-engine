#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"
#include<math\Vector2.h>

// FWD
namespace nano {
	class CoreConfig;
	namespace editor {
		class WorldSystem;
		class InputSystem;
		class RendererSystem;
	}
	namespace ecs {
		class Entity;
	}
}

namespace nano { namespace editor {  

	class EntitySelectWidget : EditorWidget, public EventObserver {
	private:
		CoreConfig* m_config;
		WorldSystem* m_entityManager;
		InputSystem* m_inputSystem;
		RendererSystem *m_renderSystem;
		ecs::Entity *m_leftClickedEntity;

		bool m_isDraggingView = false;
		math::Vector2 m_dragOrigin;
		math::Vector2 m_lastFrameMousePos;

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