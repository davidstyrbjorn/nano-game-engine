#include"../include/EditorEntryPoint.h"

namespace nano { namespace editor {

	EditorEntryPoint::EditorEntryPoint()
	{
		this->EditorInit();
	}

	EditorEntryPoint::~EditorEntryPoint()
	{
		delete m_window;
	}

	void EditorEntryPoint::EditorInit()
	{
		// Core init
		CoreInit();

		// Create window
		m_window = new EditorWindow();

		// Run the main loop
		this->MainLoop();
	}

	void EditorEntryPoint::MainLoop()
	{
		while (m_window->IsOpen()) 
		{
			m_window->Clear();

			m_window->Display();
		}
	}

} }