#pragma once

#include"EditorWidget.h"

// FWD
namespace nano {
	class CoreConfig;
}

namespace nano { namespace editor { 

	class UtilityWidget : EditorWidget {
	public:
		// Default constructor
		UtilityWidget();

		// Editor Widget Base
		void Start() override;
		void Update() override;
		void Render() override;

	private:
		CoreConfig *m_config;
	};

} }
