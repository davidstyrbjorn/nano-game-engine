#include"../include/WindowSystem.h"

#include<math\Vector2.h>
#include<ecs\Entity.h>

#include"../include/EngineConfig.h"

namespace nano { namespace engine {  

	void WindowSystem::start() {
		std::string caption = EngineConfig::getInstance()->getProjectInfo().startupLevel;
		m_window = new graphics::Window(math::Vector2(800, 600), caption);
		m_window->owner = this;
	}

	void WindowSystem::update() {

	}

	void WindowSystem::shutdown() {
		delete m_window;

		std::cout << "Window system quit correctly" << std::endl;
	}

	void WindowSystem::newLevel(const math::Vector2 & a_camSize)
	{
		m_window->SetNewWindowSize(a_camSize);
	}

	graphics::Window& WindowSystem::getWindow() {
		return *m_window;
	}

} }