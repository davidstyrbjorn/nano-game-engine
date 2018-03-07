#pragma once

#include"EngineSystemBase.h"

namespace nano {
	namespace graphics {
		class SimpleRenderer;
}
}

namespace nano { namespace engine {  

	class WorldSystem;

	class RendererSystem : public EngineSystemBase<RendererSystem> {
	friend class EngineSystemBase<RendererSystem>;

	private:
		RendererSystem() { }

		graphics::SimpleRenderer *m_renderer;
		WorldSystem* m_worldSystem;

	public:
		void start() override;
		void update() override;
		void shutdown() override;

		graphics::SimpleRenderer& getRenderer();

	};

} }