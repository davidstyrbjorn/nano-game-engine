#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"

// FWD
namespace nano {
	class CoreConfig;
}

namespace nano { namespace editor { 

	class UtilityWidget : EditorWidget, public EventObserver {
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
