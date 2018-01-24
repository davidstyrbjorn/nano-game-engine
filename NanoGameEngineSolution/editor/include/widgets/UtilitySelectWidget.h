#pragma once

#include"EditorWidget.h"

// FWD
namespace nano {
	class CoreConfig;
}

namespace nano { namespace editor {  

	class UtilitySelectWidget : EditorWidget {
	private:
		CoreConfig* m_config;

	public:
		UtilitySelectWidget();

		// Base methods
		void Start() override;
		void Update() override;
		void Render() override;
	};

} }