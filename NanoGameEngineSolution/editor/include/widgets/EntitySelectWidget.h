#pragma once

#include"EditorWidget.h"

// FWD
namespace nano {
	class CoreConfig;
	namespace editor {
		class EntityManagerSystem;
	}
}


namespace nano { namespace editor {  

	class EntitySelectWidget : EditorWidget {
	private:
		CoreConfig* m_config;
		EntityManagerSystem* m_entityManager;

	public:
		EntitySelectWidget();

		// Base class 
		void Start() override;
		void Update() override;
		void Render() override;
	};

} }