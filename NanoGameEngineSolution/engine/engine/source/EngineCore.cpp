#include"../include/EngineCore.h"

#include<graphics\Window.h>
#include<math\Vector4.h>

namespace nano { namespace engine {  

EngineCore::~EngineCore()
{

}

void EngineCore::shutdown()
{
	// Call shutdown on every system
	m_windowSystem->shutdown();
	m_worldSystem->shutdown();
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

	// TESTING
	m_worldSystem->createNewEntity("mr.deaf");
	m_worldSystem->createNewEntity("player");

	// Start the main loop
	mainLoop();
}

void EngineCore::mainLoop()
{
	// Enter the main loop
	while (m_windowSystem->getWindow().IsOpen()) 
	{
		m_windowSystem->getWindow().Clear(math::Vector4(0.4f, 0.4f, 0.4f, 0));

		m_worldSystem->update();

		m_windowSystem->getWindow().Display();
	}

	shutdown();
}

} }