#include"../include/EngineCore.h"

#include<graphics\Window.h>
#include<math\Vector4.h>

namespace nano { namespace engine {  

EngineCore::~EngineCore()
{

}

void EngineCore::init()
{
	// Init every system
	m_engineConfig = EngineConfig::getInstance();
	m_engineConfig->loadProjectInfo();

	m_windowSystem = WindowSystem::getInstance();
	m_windowSystem->start();

	// Start the main loop
	mainLoop();
}

void EngineCore::mainLoop()
{
	// Enter the main loop
	while (m_windowSystem->getWindow().IsOpen()) 
	{
		m_windowSystem->getWindow().Clear(math::Vector4(0.4f, 0.4f, 0.4f, 0));

		m_windowSystem->getWindow().Display();
	}
}

} }