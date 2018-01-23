#pragma once

#include"EditorSystem.h"

// FWD
namespace nano {
	namespace graphics {
		class SimpleRenderer;
	}
	namespace editor {
		class EntityManagerSystem;
	}
}

namespace nano { namespace editor { 

	class RendererSystem : public EditorSystem {
	private:
		// Private constructor (singleton)
		RendererSystem() { }
		
		// The one sole instance
		static RendererSystem* _instance;

	public:
		// Singleton connection
		static RendererSystem* Instance();

	private:
		graphics::SimpleRenderer* m_renderer;
		EntityManagerSystem* m_entityManager;

	public:
		// EditorSystem base class
		void Start() override;
		void Update() override;
		void Quit() override;

		// Rendering routines
		graphics::SimpleRenderer& GetSimpleRenderer();
	};

} } 