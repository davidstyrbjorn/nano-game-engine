#include"../include/systems/RendererSystem.h"

#include"graphics\Simple_Renderer.h"

#include"../include/systems/WorldSystem.h"

#define GLEW_STATIC
#include<GL\glew.h>

namespace nano { namespace editor { 

	RendererSystem* RendererSystem::_instance = nullptr;
	RendererSystem* RendererSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new RendererSystem();
		return _instance;
	}

	void RendererSystem::Start(const char* a_vertexPath, const char* a_fragmentPath)
	{
		// Create the renderer (from core)
		m_renderer = new graphics::SimpleRenderer(a_vertexPath, a_fragmentPath, math::Vector2(1200,800));
	
		// Get the entity manager
		m_entityManager = WorldSystem::Instance();
	}

	void RendererSystem::Update()
	{
		// Submit every entity to be rendered from the entity manager system here!
		std::vector<ecs::Entity*> entityList = m_entityManager->GetEntityListCopy();
		for (ecs::Entity* entity : entityList) {
			if (entity->GetRenderableComponent() != nullptr && entity->GetState() == ecs::ECSStates::ACTIVE) {
				m_renderer->Submit(entity->GetRenderableComponent());
			}
		}
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