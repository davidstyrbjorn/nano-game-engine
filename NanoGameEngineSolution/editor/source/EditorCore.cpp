#include"../include/EditorCore.h"

#include<ecs\ECSInclude.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\TriangleComponent.h>

#include<graphics\GraphicsInclude.h>

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

		// Renderer System
		m_rendererSystem = RendererSystem::Instance();
		m_rendererSystem->Start();

		// Test
		//ecs::Entity* testEntity = new ecs::Entity();
		//testEntity->Start();
		//testEntity->AddComponent(new ecs::RectangleComponent(math::Vector2(20, 20), math::Vector4(1, 1, 1, 1)))->Start();
		//
		//m_entityManagerSystem->AddNewEntity(testEntity);

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

			// Rendering
			m_rendererSystem->GetSimpleRenderer().Begin();
			m_rendererSystem->Update();
			m_rendererSystem->GetSimpleRenderer().Flush(); 

			// Update the entity manager system
			m_entityManagerSystem->Update();

			// Post-frame
			m_windowSystem->GetWindow().Display();
		}
	}

} }