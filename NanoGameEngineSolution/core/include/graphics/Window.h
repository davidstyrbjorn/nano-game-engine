#pragma once

#include<string>

struct GLFWwindow;

namespace nano {
	namespace math {
		class Vector2;
		class Vector4;
	}
	class CoreConfig;
}

namespace nano { namespace graphics { 

	class WindowOwner {
	public:
		// Callback polymorphic method/s
		virtual void WindowResized(int a_width, int a_height) { }
	};

	class Window {
	public:
		// Constructor
		Window(const math::Vector2& a_windowSize, const std::string& a_windowCaption = "Nano Game Engine");

		// Destructor
		~Window();

		// Public methods
		void Close();
		void Clear();
		void Clear(const math::Vector4 a_clearColor);
		void Display();
		void SetNewWindowSize(math::Vector2 a_size);

		// Public methods (getters)
		const bool IsOpen();
		const GLFWwindow* GetGLFWwindow();

		// GLFW callbacks
		static friend void window_size_callback(GLFWwindow* window, int width, int height);

		// This will be either editor::WindowSystem or engine::WindowSystem!
		WindowOwner *owner;

	private:
		CoreConfig *config;
		GLFWwindow *m_glfwWindow;
	};

} } 