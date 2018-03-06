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
	m_inputSystem->shutdown();
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
		m_inputSystem->update();

		//for (InputEvent event : m_inputSystem->getPolledEvents()) {
		//	if (event.type == INPUT_TYPE::MOUSE_RELEASE) {
		//		std::cout << "mouse released" << std::endl;
		//	}
		//	if (event.type == INPUT_TYPE::MOUSE_PRESSED) {
		//		std::cout << "mouse pressed" << std::endl;
		//	}			
		//	if (event.type == INPUT_TYPE::KEY_PRESSED) {
		//		std::cout << "key pressed" << std::endl;
		//	}
		//	if (event.type == INPUT_TYPE::KEY_RELEASE) {
		//		std::cout << "key release" << std::endl;
		//	}
		//	if (event.type == INPUT_TYPE::KEY_HOLD) {
		//		std::cout << "key hold" << std::endl;
		//	}
		//}

		m_inputSystem->flushEvents();
		m_windowSystem->getWindow().Display();
	}

	shutdown();
}

} }