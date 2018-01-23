#pragma once

// Classes from core
#include<graphics\GraphicsInclude.h>
#include<math\MathInclude.h>

// Editor classes
#include"systems\WindowSystem.h"
#include"systems\EntityManagerSystem.h"
#include"systems\RendererSystem.h"

namespace nano { namespace editor { 

	class EditorCore {
	private:
		// Editor systems 
		WindowSystem *m_windowSystem;
		EntityManagerSystem *m_entityManagerSystem;
		RendererSystem *m_rendererSystem;

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