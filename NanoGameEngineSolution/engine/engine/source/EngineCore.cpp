#include"../include/EngineCore.h"

#include<graphics\Window.h>
#include<math\Vector4.h>
#include<graphics\Simple_Renderer.h>

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
	m_levelSystem->shutdown();
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

	m_levelSystem = LevelSystem::getInstance();
	m_levelSystem->start();

	m_scriptingSystem = ScriptingSystem::getInstance();
	m_scriptingSystem->start();

	// Start the main loop
	mainLoop();
}

void EngineCore::mainLoop()
{
	// Enter the main loop
	while (m_windowSystem->getWindow().IsOpen()) 
	{
		m_windowSystem->getWindow().Clear(math::Vector4(0.1f, 0.1f, 0.1f, 0));

		m_scriptingSystem->update();
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