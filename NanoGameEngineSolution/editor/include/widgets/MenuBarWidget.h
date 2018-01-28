#pragma once

#include"EditorWidget.h"

// FWD
namespace nano {
	class CoreConfig;
}

namespace nano { namespace editor { 

	class MenuBarWidget : EditorWidget {
	public:
		// Default constructor
		MenuBarWidget();

		// Base class
		void Start() override;
		void Update() override;
		void Render() override;

	private:
		CoreConfig *m_config;
		bool m_showCreditsWidget = false;
	};

} }