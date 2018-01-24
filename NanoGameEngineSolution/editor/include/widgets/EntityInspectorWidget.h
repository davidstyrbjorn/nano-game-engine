#pragma once

#include"EditorWidget.h"

// FWD
namespace nano {
	class CoreConfig;
}

namespace nano {
	namespace editor {

		class EntityInspectorWidget : EditorWidget {
		private:
			CoreConfig* m_config;

		public:
			EntityInspectorWidget();

			// Base methods
			void Start() override;
			void Update() override;
			void Render() override;
		};

	}
}