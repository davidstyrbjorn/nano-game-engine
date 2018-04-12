#pragma once

// Classes from core
#include<graphics\GraphicsInclude.h>
#include<math\MathInclude.h>
#include<Clock.h>

// Editor classes
#include"systems\WindowSystem.h"
#include"systems\WorldSystem.h"
#include"systems\RendererSystem.h"
#include"systems\EditorWidgetSystem.h"
#include"systems\InputSystem.h"
#include"systems\SoundSystem.h"
#include"systems\LevelSystem.h"
#include"systems\AssetSystem.h"

#define FPS 60
#define MS 1000/FPS

#define NANO_EDITOR_API __declspec(dllexport)

namespace nano { namespace editor { 

	class NANO_EDITOR_API EditorCore {
	private:
		// Editor systems 
		WindowSystem *m_windowSystem;
		InputSystem *m_inputSystem;
		WorldSystem *m_WorldSystem;
		RendererSystem *m_rendererSystem;
		EditorWidgetSystem *m_editorWidgetSystem;
		SoundSystem *m_soundSystem;
		LevelSystem *m_levelSystem;
		AssetSystem* m_assetSystem;
		CoreConfig *m_config;

		// Other
		Clock m_fpsClock;
		Clock m_frameClock;

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