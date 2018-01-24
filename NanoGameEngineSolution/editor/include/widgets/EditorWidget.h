#pragma once

#include"Widget.h"

namespace nano { namespace editor {
	
	class EditorWidget {
	public:
		// Called on editor start
		// Initalize the widget (systems and members)
		virtual void Start() = 0;

		// Called on editor update
		// Updates the widgets behaviours
		virtual void Update() = 0;

		// Called on editor render
		// Renders the ImGui stuff
		virtual void Render() = 0;
	};
	
} }