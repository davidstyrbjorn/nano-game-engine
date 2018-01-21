#pragma once

// Base
#include<CoreEntryPoint.h>

// Classes from core
#include<graphics\GraphicsInclude.h>

// Editor classes
#include"graphics\EditorWindow.h"

namespace nano { namespace editor { 

	class EditorEntryPoint : public CoreEntryPoint {
	private:
		EditorWindow *m_window;

	public:
		// Default constructor
		EditorEntryPoint();

		// Destructor
		~EditorEntryPoint();

		// Initialize the editor
		void EditorInit();

		// Main editor loop this is the root of the program
		void MainLoop();
	};

} } 