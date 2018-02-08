#include"../include/EditorCore.h"

#include<ecs\ECSInclude.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\SoundComponent.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\TriangleComponent.h>
#include<ecs\components\SpriteComponent.h>

#include<graphics\GraphicsInclude.h>

#include"../include/DearImGui/imgui.h"
#include"../include/DearImGui/imgui_glfw.h"

#include<GLFW\glfw3.h>

#include<InputDefinitions.h>

#include<thread>

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
		m_config = CoreConfig::Instance();
		m_config->SetShaderPaths("../../vertex.txt", "../../fragment.txt");
		m_config->SetErrorTexturePath("..//resources//error_texture.png");

		// Start every editor system

		// Window System (1200 by 800)
		m_windowSystem = WindowSystem::Instance();
		m_windowSystem->Start();

		// Create input system now that the window is up and running
		m_inputSystem = InputSystem::Instance();
		m_inputSystem->Start();

		// Sound system (OpenAL device&context)
		m_soundSystem = SoundSystem::Instance();
		m_soundSystem->Start();

		// Entity Manager System
		m_WorldSystem = WorldSystem::Instance();
		m_WorldSystem->Start();

		// Renderer System
		m_rendererSystem = RendererSystem::Instance();
		m_rendererSystem->Start();

		// Editor Widget System
		m_editorWidgetSystem = EditorWidgetSystem::Instance();
		m_editorWidgetSystem->Start();

		/////////////////////////////////////////////////////////////////////

		// Test
		ecs::Entity* testEntity = new ecs::Entity("Rectangle");
		testEntity->Start();
		testEntity->m_transform->position = math::Vector2(400, 100);
		testEntity->m_transform->size = math::Vector2(100, 40);
		testEntity->AddComponent(new ecs::RectangleComponent(math::Vector4(0.4, 0.1, 0.9, 1)))->Start();
		testEntity->AddComponent(new ecs::SoundComponent("D:\\temp\\sound.wav"));
		m_WorldSystem->AddNewEntity(testEntity);
		
		ecs::Entity* triangle = new ecs::Entity("Triangle");
		triangle->Start();
		triangle->m_transform->position = math::Vector2(400, 200);
		triangle->m_transform->size = math::Vector2(100, 100);
		triangle->AddComponent(new ecs::TriangleComponent(math::Vector4(1, 0.1, 0.1, 1)))->Start();
		m_WorldSystem->AddNewEntity(triangle);
		triangle->SetState(ecs::ECSStates::DISABLED);
		
		ecs::Entity* Sprite = new ecs::Entity("Sprite(png)");
		Sprite->Start();
		Sprite->AddComponent(new ecs::SpriteComponent("C:\\temp\\no\\cat.png"))->Start();
		m_WorldSystem->AddNewEntity(Sprite);
		
		ecs::Entity* Sprite2 = new ecs::Entity("Sprit2(jpg)");
		Sprite2->Start();
		Sprite2->AddComponent(new ecs::SpriteComponent("C:\\temp\\sample.jpg"))->Start();
		m_WorldSystem->AddNewEntity(Sprite2);

		/////////////////////////////////////////////////////////////////////

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
				m_windowSystem->GetWindow().Clear();

				// Events stuff
				m_inputSystem->Update();

				// Update the entity manager system
				m_WorldSystem->Update();

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

				// Final
				frameCount++;
				m_frameClock.Reset();
			}
		}
	}

} }