#pragma once

// Classes from core
#include<graphics\GraphicsInclude.h>
#include<math\MathInclude.h>
#include<CoreConfig.h>
#include<Clock.h>

// Editor classes
#include"systems\WindowSystem.h"
#include"systems\WorldSystem.h"
#include"systems\RendererSystem.h"
#include"systems\EditorWidgetSystem.h"
#include"systems\InputSystem.h"
#include"systems\SoundSystem.h"

// @ Remove 
#include<sound\SoundContextDevice.h>

namespace nano { namespace editor { 

	class EditorCore {
	private:
		// Editor systems 
		WindowSystem *m_windowSystem;
		InputSystem *m_inputSystem;
		WorldSystem *m_WorldSystem;
		RendererSystem *m_rendererSystem;
		EditorWidgetSystem *m_editorWidgetSystem;
		SoundSystem *m_soundSystem;
		CoreConfig *m_config;
		openal::ContextDevice *contextDevice;

		// Other
		Clock m_fpsClock;

	public:
		// Default constructor
		EditorCore();

		// Destructor
		~EditorCore();

		// Initialize the editor
		void Init();

		// Main editor loop this is the root of the program
		void MainLoop();
	};

} } 