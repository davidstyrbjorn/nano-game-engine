#pragma once

#include<graphics\Window.h>

#include"EditorSystem.h"

namespace nano { namespace editor { 

	class WindowSystem : public EditorSystem<WindowSystem>, graphics::WindowOwner {
		friend class EditorSystem<WindowSystem>;
	private:
		// Private constructor (singleton)
		WindowSystem() { }

	private:
		// Window system members
		graphics::Window* m_window;

	public:
		// Base class methods
		void Start() override;
		void Update() override;
		void Quit() override;

		// Callback
		void WindowResized(int a_width, int a_height) override;

		// Window routines
		graphics::Window& GetWindow();

	};

} }