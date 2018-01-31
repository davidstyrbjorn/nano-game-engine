#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"
#include<math\Vector2.h>

// FWD
namespace nano {
	class CoreConfig;
	namespace ecs {
		class Entity;
	}
	namespace editor {
		class InputSystem;
		class RendererSystem;
	}
}

namespace nano {
	namespace editor {

		class EntityInspectorWidget : EditorWidget, public EventObserver {
		private:
			CoreConfig* m_config;
			InputSystem* m_inputSystem;
			RendererSystem *m_renderSystem;
			ecs::Entity *m_entityToInspect;

			bool m_isDraggingEntity = false;
			math::Vector2 m_dragDeltaPosition;

		public:
			EntityInspectorWidget();

			// Base methods
			void Start() override;
			void Update() override;
			void Render() override;

			void OnEntityClick(std::string a_id) override;
			void OnEntityDestroyed(std::string a_id) override;
		};

	}
}