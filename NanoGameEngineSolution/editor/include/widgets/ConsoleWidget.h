#pragma once

#include"EditorWidget.h"

// FWD
namespace nano {
	class CoreConfig;
}

namespace nano {
	namespace editor {

		class ConsoleWidget : EditorWidget {
		private:
			CoreConfig* m_config;

		public:
			ConsoleWidget();

			// Base methods
			void Start() override;
			void Update() override;
			void Render() override;
		};

	}
}