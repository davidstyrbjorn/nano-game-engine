#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"

// FWD
namespace nano {
	class CoreConfig;
	namespace editor {
		class WorldSystem;
	}
}


namespace nano { namespace editor {  

	class EntitySelectWidget : EditorWidget, public EventObserver {
	private:
		CoreConfig* m_config;
		WorldSystem* m_entityManager;

	public:
		EntitySelectWidget();

		// Base class 
		void Start() override;
		void Update() override;
		void Render() override;
	};

} }