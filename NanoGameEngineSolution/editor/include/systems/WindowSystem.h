#pragma once

#include<graphics\Window.h>

#include"EditorSystem.h"

namespace nano { namespace editor { 

	class WindowSystem : EditorSystem, graphics::WindowOwner {
	private:
		// Private constructor (singleton)
		WindowSystem() { }

		static WindowSystem* _instance;

	public:
		// Singleton connection
		static WindowSystem* Instance();
		
	private:
		// Window system members
		graphics::Window* m_window;

	public:
		// Base class methods
		void Start() override;
		void Update() override;
		void Quit() override;

		// @ HOTFIX
		void WindowResized(int a_width, int a_height) override;

		// Window routines
		graphics::Window& GetWindow();

	};

} }