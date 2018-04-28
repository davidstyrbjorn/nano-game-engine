#include"../include/systems/RendererSystem.h"

#include"graphics\Simple_Renderer.h"

#include"../include/systems/WorldSystem.h"

#include"ecs\RenderableComponent.h"

namespace nano { namespace editor { 

	void RendererSystem::Start(const char* a_vertexPath, const char* a_fragmentPath)
	{
		// Create the renderer (from core)
		m_renderer = new graphics::SimpleRenderer(a_vertexPath, a_fragmentPath, math::Vector2(1200,800));
	
		// Get the entity manager
		m_entityManager = WorldSystem::getInstance();
	}

	void RendererSystem::Update()
	{
		// Submit every entity to be rendered from the entity manager system here!
		//std::vector<ecs::Entity> entityList = m_entityManager->getArray();
		//for (ecs::Entity entity : entityList) {
		//	if (entity.Renderable() != nullptr && entity.IsActive()) {
		//		m_renderer->Submit(entity.Renderable());
		//	}
		//}
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