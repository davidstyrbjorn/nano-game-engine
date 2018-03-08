#pragma once

#include"EngineSystemBase.h"
#include<graphics\Window.h>

namespace nano { namespace engine {  

	class WindowSystem : public EngineSystemBase<WindowSystem>, public graphics::WindowOwner {
	friend class EngineSystemBase<WindowSystem>;

	private:
		WindowSystem() {}

		graphics::Window *m_window;

	public:
		void start() override;
		void update() override;
		void shutdown() override;
		void newLevel(const math::Vector2& a_camSize);

		// Window routines called from core loop
		graphics::Window& getWindow();
	};

} }