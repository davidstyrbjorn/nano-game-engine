#include"../include/EditorCore.h"

#include<ecs\ECSInclude.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\TriangleComponent.h>

namespace nano { namespace editor { 

	EditorCore::~EditorCore()
	{
		// Call Quit on every system
		m_windowSystem->Quit();
		m_entityManagerSystem->Quit();
	}

	EditorCore::EditorCore()
	{
		this->Init();
	}

	void EditorCore::Init()
	{
		// Start every system

		// Window System
		m_windowSystem = WindowSystem::Instance();
		m_windowSystem->Start();

		// Entity Manager System
		m_entityManagerSystem = EntityManagerSystem::Instance();
		m_entityManagerSystem->Start();

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

			// Update the entity manager system
			m_entityManagerSystem->Update();

			// Post-frame
			m_windowSystem->GetWindow().Display();
		}
	}

} }