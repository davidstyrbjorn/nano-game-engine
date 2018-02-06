#include"../include/systems/WindowSystem.h"

#include<math\Vector2.h>

#include"../include/systems/RendererSystem.h"
#include<graphics\Simple_Renderer.h>
#include<graphics\Camera.h>

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
		m_window->owner = this;
	}

	void WindowSystem::Update()
	{

	}

	void WindowSystem::Quit()
	{
		delete m_window;
		std::cout << "Window system quit correctly" << std::endl;
	}

	void WindowSystem::WindowResized(int a_width, int a_height)
	{
		//RendererSystem::Instance()->GetSimpleRenderer().GetCamera()->SetSize(math::Vector2(a_width, a_height));
	}

	graphics::Window & WindowSystem::GetWindow()
	{
		return *m_window;
	}

}
}