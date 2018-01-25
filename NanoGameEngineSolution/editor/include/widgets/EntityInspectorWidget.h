#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"

// FWD
namespace nano {
	class CoreConfig;
	namespace ecs {
		class Entity;
	}
}

namespace nano {
	namespace editor {

		class EntityInspectorWidget : EditorWidget, public EventObserver {
		private:
			CoreConfig* m_config;
			ecs::Entity *m_entityToInspect;

		public:
			EntityInspectorWidget();

			// Base methods
			void Start() override;
			void Update() override;
			void Render() override;

			// Concept code @
			void OnEntityClick(std::string a_id) override;
			void OnEntityDestroyed(std::string a_id) override;
		};

	}
}