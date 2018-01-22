#include"../include/EditorCore.h"

namespace nano { namespace editor { 

	EditorCore::~EditorCore()
	{
		// Call Quit on every system
		m_windowSystem->Quit();
	}

	EditorCore::EditorCore()
	{
		this->Init();
	}

	void EditorCore::Init()
	{
		// Start every system
		m_windowSystem = WindowSystem::Instance();
		m_windowSystem->Start();

		// Start the main loop method
		this->MainLoop();
	}

	void EditorCore::MainLoop()
	{
		// Main editor loop 
		// Here we update every system
		// Here we control the editor at run time
		while (m_windowSystem->GetWindow().IsOpen()) 
		{
			// Pre-frame 
			m_windowSystem->GetWindow().Clear();

			// 

			// Post-frame
			m_windowSystem->GetWindow().Display();
		}
	}

} }