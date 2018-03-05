#pragma once

#include"EngineSystemBase.h"

namespace nano {
	namespace graphics {
		class Window;
} }

namespace nano { namespace engine {  

	class WindowSystem : public EngineSystemBase<WindowSystem> {
	friend class EngineSystemBase<WindowSystem>;

	private:
		WindowSystem() {}

		graphics::Window *m_window;

	public:
		void start() override;
		void update() override;
		void shutdown() override;

		// Window routines called from core loop
		graphics::Window& getWindow();
	};

} }