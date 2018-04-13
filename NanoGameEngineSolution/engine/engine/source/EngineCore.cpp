#include"../include/EngineCore.h"

#include<graphics\Window.h>
#include<math\Vector4.h>
#include<graphics\Simple_Renderer.h>

#include<thread>
#include<Windows.h>

namespace nano { namespace engine {

EngineCore::EngineCore()
{
	init();

	std::thread th(&EngineCore::mainLoop, this);
	std::thread th2(&EngineCore::fixedLoop, this);

	th.join();
	th2.join();
}

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
	m_assetSystem->shutdown();
}

void EngineCore::init()
{
	// Init every system
	m_engineConfig = EngineConfig::getInstance();
	m_engineConfig->loadProjectInfo();

	m_assetSystem = AssetSystem::getInstance();
	m_assetSystem->start();

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

	// Start the main loop
	mainLoop();
}

void EngineCore::mainLoop()
{
	// Enter the main loop
	while (m_windowSystem->getWindow().IsOpen()) 
	{
		// Clear the window for new frame
		m_windowSystem->getWindow().Clear(math::Vector4(0.1f, 0.1f, 0.1f, 0));

		// Regular Update
		m_worldSystem->update();
		m_inputSystem->update();

		// Reset the renderer for this frame
		m_rendererSystem->getRenderer().Begin();
		// This collects the data to be drawn
		m_rendererSystem->update();
		// Flush the renderer (draw calls get called here)
		m_rendererSystem->getRenderer().Flush();

		// Finish the frame
		m_inputSystem->flushEvents();
		m_windowSystem->getWindow().Display();
	}

	shutdown();
}

void EngineCore::fixedLoop()
{				 				
	while (m_windowSystem->getWindow().IsOpen()) {
		std::cout << "Fixed Update" << std::endl;
	}
}

} }