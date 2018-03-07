#include"../include/RendererSystem.h"

#include"../include/EngineConfig.h"
#include"../include/WorldSystem.h"

#include<graphics\Simple_Renderer.h>
#include<ecs\Entity.h>
#include<graphics\Renderable.h>
#include<ecs\ECS.h>

namespace nano { namespace engine {  

	void RendererSystem::shutdown()
	{
		delete m_renderer;
	}

	void RendererSystem::start()
	{
		// Create the renderer (from core project)
		m_renderer = new graphics::SimpleRenderer("resources\\vertex.txt", "resources\\fragment.txt", math::Vector2(800, 600));
	
		// Get world system
		m_worldSystem = WorldSystem::getInstance();
	}

	void RendererSystem::update()
	{
		// Submit every enttiy to be rendererd from the world system
		for (ecs::Entity* entity : m_worldSystem->getEntityListReference()) {
			if (entity->GetRenderableComponent() != nullptr && entity->GetState() == ecs::ECSStates::ACTIVE) {
				m_renderer->Submit(entity->GetRenderableComponent());
			}
		}
	}

	graphics::SimpleRenderer & RendererSystem::getRenderer()
	{
		return *m_renderer;
	}

} }