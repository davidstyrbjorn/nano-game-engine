#pragma once

#include<string>

struct GLFWwindow;

namespace nano {
	namespace math {
		class Vector2;
	}
}

namespace nano { namespace graphics { 

	class Window {
	public:
		// Constructor
		Window(const math::Vector2& a_windowSize, const std::string& a_windowCaption = "Nano Game Engine");

		// Destructor
		~Window();

		// Public methods
		void Close();
		void Clear();
		void Display();

		// Public methods (getters)
		const bool IsOpen();
		const math::Vector2& GetWindowSize();
		const GLFWwindow* GetGLFWwindow();

	protected:
		GLFWwindow *m_glfwWindow;
	};

} } 