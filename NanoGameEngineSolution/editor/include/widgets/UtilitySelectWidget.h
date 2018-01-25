#pragma once

#include"EditorWidget.h"
#include"../EventObserver.h"

// FWD
namespace nano {
	class CoreConfig;
}

namespace nano { namespace editor {  

	class UtilitySelectWidget : EditorWidget, public EventObserver {
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