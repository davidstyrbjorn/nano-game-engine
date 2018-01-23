#include"../include/systems/WindowSystem.h"

#include<math\Vector2.h>

namespace nano { namespace editor { 
	
	WindowSystem* WindowSystem::_instance = nullptr;

	WindowSystem * WindowSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new WindowSystem();
		return _instance;
		return nullptr;
	}

	void WindowSystem::Start()
	{
		m_window = new graphics::Window(math::Vector2(1200, 800), "Nano Editor (Windows Standalone x86)");
	}

	void WindowSystem::Update()
	{

	}

	void WindowSystem::Quit()
	{
		delete m_window;
		std::cout << "Window system quit correctly" << std::endl;
	}

	graphics::Window & WindowSystem::GetWindow()
	{
		return *m_window;
	}

}
}