#include"../include/WindowSystem.h"

#include<graphics\Window.h>
#include<math\Vector2.h>

#include"../include/EngineConfig.h"

namespace nano { namespace engine {  

	void WindowSystem::start() {
		std::string caption = EngineConfig::getInstance()->getProjectInfo().startupLevel;
		m_window = new graphics::Window(math::Vector2(800, 600), caption);
	}

	void WindowSystem::update() {

	}

	void WindowSystem::shutdown() {
		delete m_window;

		std::cout << "Window system quit correctly" << std::endl;
	}

	graphics::Window& WindowSystem::getWindow() {
		return *m_window;
	}

} }