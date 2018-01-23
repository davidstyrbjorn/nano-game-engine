#include"../include/systems/RendererSystem.h"

#include<graphics\GraphicsInclude.h>

namespace nano { namespace editor { 

	RendererSystem* RendererSystem::_instance = nullptr;
	RendererSystem* RendererSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new RendererSystem();
		return _instance;
	}

	void RendererSystem::Start()
	{
		m_renderer = new graphics::SimpleRenderer();
	}

	void RendererSystem::Update()
	{
		// Submit every entity to be rendered from the entity manager system here!
	}

	void RendererSystem::Quit()
	{
		delete m_renderer;
	}

	graphics::SimpleRenderer & RendererSystem::GetSimpleRenderer()
	{
		return *m_renderer;
	}

} }