#include"../include/EditorCore.h"

#include<GLFW\glfw3.h>

#include"../include/LevelParser.h"
#include"../include/systems/EditorConfig.h"

namespace nano { namespace editor { 

	EditorCore::~EditorCore()
	{
		// Call Quit on every system
		m_windowSystem->Quit();
		m_WorldSystem->Quit();
		m_editorWidgetSystem->Quit();
		m_soundSystem->Quit();
	}

	EditorCore::EditorCore()
	{
		this->Init();
	}

	void EditorCore::Init()
	{
		// Start every editor system
		EditorConfig::Instance()->loadProjectInfo();
		EditorConfig::Instance()->setCurrentLevelName("none");
		EditorConfig::Instance()->setClearColor(math::Vector4(0.2, 0.2f, 0.2f, 0.0f));

		// Window System (1200 by 800)
		m_windowSystem = WindowSystem::getInstance();
		m_windowSystem->Start();

		// Create input system now that the window is up and running
		m_inputSystem = InputSystem::getInstance();
		m_inputSystem->Start();

		// Sound system (OpenAL device&context)
		m_soundSystem = SoundSystem::getInstance();
		m_soundSystem->Start();

		// Entity Manager System
		m_WorldSystem = WorldSystem::getInstance();
		m_WorldSystem->Start();

		// Renderer System
		m_rendererSystem = RendererSystem::getInstance();
		m_rendererSystem->Start("resources//vertex.txt", "resources//fragment.txt");

		// Editor Widget System
		m_editorWidgetSystem = EditorWidgetSystem::getInstance();
		m_editorWidgetSystem->Start();

		// Start the main loop method
		this->MainLoop();
	}

	void EditorCore::MainLoop()
	{
		m_fpsClock.Reset();
		m_fpsClock.Start();
		int frameCount = 0;

		m_frameClock.Reset();
		m_frameClock.Start();

		EditorConfig *c = EditorConfig::Instance();

		// Main editor loop 
		// Here we update every system
		// Here we control the editor at run time
		while (m_windowSystem->GetWindow().IsOpen()) 
		{
			if (m_fpsClock.GetTicks() >= 1000) {
				//std::cout << frameCount << std::endl;
				frameCount = 0;
				m_fpsClock.Reset();
			}

			if (m_frameClock.GetTicks() >= MS) {
				// Pre-frame 
				m_windowSystem->GetWindow().Clear(c->getClearColor());

				// Events stuff
				m_inputSystem->Update();

				// Update the entity manager system
				m_WorldSystem->Update();

#pragma region		    RENDERING
				// Rendering
				m_rendererSystem->GetSimpleRenderer().Begin();
				m_rendererSystem->GetSimpleRenderer().SubmitGridData();
				m_editorWidgetSystem->Begin();

				m_rendererSystem->Update();
				m_editorWidgetSystem->Update();

				m_rendererSystem->GetSimpleRenderer().Flush();
				m_editorWidgetSystem->Flush();
#pragma endregion

				// Post-frame
				m_inputSystem->FlushEvents();
				m_windowSystem->GetWindow().Display();

				// Final
				frameCount++;
				m_frameClock.Reset();
			}
		}
	}

} }