#include"../include/EditorCore.h"

#include<ecs\ECSInclude.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\TriangleComponent.h>

#include<graphics\GraphicsInclude.h>

#include"../include/DearImGui/imgui.h"
#include"../include/DearImGui/imgui_glfw.h"

#include<GLFW\glfw3.h>

#include<InputDefinitions.h>

namespace nano { namespace editor { 

	EditorCore::~EditorCore()
	{
		// Call Quit on every system
		m_windowSystem->Quit();
		m_entityManagerSystem->Quit();
		m_editorWidgetSystem->Quit();
	}

	EditorCore::EditorCore()
	{
		this->Init();
	}

	void EditorCore::Init()
	{
		m_config = CoreConfig::Instance();
		m_config->SetShaderPaths("../../vertex.txt", "../../fragment.txt");

		// Start every editor system

		// Window System (1200 by 800)
		m_windowSystem = WindowSystem::Instance();
		m_windowSystem->Start();

		// Create input system now that the window is up and running
		m_inputSystem = InputSystem::Instance();
		m_inputSystem->Start();

		// Entity Manager System
		m_entityManagerSystem = EntityManagerSystem::Instance();
		m_entityManagerSystem->Start();

		// Renderer System
		m_rendererSystem = RendererSystem::Instance();
		m_rendererSystem->Start();

		// Editor Widget System
		m_editorWidgetSystem = EditorWidgetSystem::Instance();
		m_editorWidgetSystem->Start();

		/////////////////////////////////////////////////////////////////////

		// Test
		//ecs::Entity* testEntity = new ecs::Entity();
		//testEntity->Start();
		//testEntity->AddComponent(new ecs::RectangleComponent(math::Vector2(100, 100), math::Vector4(0.4, 0.1, 0.9, 1)))->Start();
		//
		//m_entityManagerSystem->AddNewEntity(testEntity);

		/////////////////////////////////////////////////////////////////////

		// Start the main loop method
		this->MainLoop();
	}

	void EditorCore::MainLoop()
	{
		m_fpsClock.Reset();
		m_fpsClock.Start();
		int FPS = 0;

		// Main editor loop 
		// Here we update every system
		// Here we control the editor at run time
		while (m_windowSystem->GetWindow().IsOpen()) 
		{
			// Pre-frame 
			m_windowSystem->GetWindow().Clear();

			// Events stuff
			m_inputSystem->Update();

			// Update the entity manager system
			m_entityManagerSystem->Update();

#pragma region		    RENDERING
			// Rendering
			m_rendererSystem->GetSimpleRenderer().Begin();
			m_editorWidgetSystem->Begin();

			m_rendererSystem->Update();
			m_editorWidgetSystem->Update();

			m_rendererSystem->GetSimpleRenderer().Flush(); 
			m_editorWidgetSystem->Flush();
#pragma endregion

			// Post-frame
			m_inputSystem->FlushEvents();
			m_windowSystem->GetWindow().Display();
		}
	}

} }