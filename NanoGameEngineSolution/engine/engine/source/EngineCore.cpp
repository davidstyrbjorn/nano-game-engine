#include"../include/EngineCore.h"

#include<graphics\Window.h>
#include<math\Vector4.h>
#include<graphics\Simple_Renderer.h>

#include"../include/RendererSystem.h"

// TEST INCLUDE
#include<ecs\Entity.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\TransformComponent.h>

namespace nano { namespace engine {  

EngineCore::~EngineCore()
{

}

void EngineCore::shutdown()
{
	// Call shutdown on every system
	m_inputSystem->shutdown();
	m_windowSystem->shutdown();
	m_worldSystem->shutdown();
	m_rendererSystem->shutdown();
}

void EngineCore::init()
{
	// Init every system
	m_engineConfig = EngineConfig::getInstance();
	m_engineConfig->loadProjectInfo();

	m_windowSystem = WindowSystem::getInstance();
	m_windowSystem->start();

	m_worldSystem = WorldSystem::getInstance();
	m_worldSystem->start();

	m_inputSystem = InputSystem::getInstance();
	m_inputSystem->start();

	m_rendererSystem = RendererSystem::getInstance();
	m_rendererSystem->start();

	// TESTING
	ecs::Entity* couch = m_worldSystem->createNewEntity("mr.deaf");
	couch->AddComponent(new ecs::RectangleComponent(math::Vector4(1, 0, 0, 1)));
	couch->m_transform->size = math::Vector2(100, 100);
	couch->m_transform->position = math::Vector2(350, 250);
	m_worldSystem->createNewEntity("player");

	// Start the main loop
	mainLoop();
}

void EngineCore::mainLoop()
{
	// Enter the main loop
	while (m_windowSystem->getWindow().IsOpen()) 
	{
		m_windowSystem->getWindow().Clear(math::Vector4(0.2f, 0.2f, 0.2f, 0));

		m_worldSystem->update();
		m_inputSystem->update();

		// Reset the renderer forthis frame
		m_rendererSystem->getRenderer().Begin();

		m_rendererSystem->update();

		// Flush the renderer (draw calls get called here)
		m_rendererSystem->getRenderer().Flush();

		m_inputSystem->flushEvents();
		m_windowSystem->getWindow().Display();
	}

	shutdown();
}

} }