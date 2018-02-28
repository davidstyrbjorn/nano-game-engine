#include"../include/graphics/Window.h"

#include"../include/math/Vector2.h"
#include"../include/math/Vector4.h"

#include<GLFW\glfw3.h>

namespace nano { namespace graphics {

	Window::Window(const math::Vector2 & a_windowSize, const std::string & a_windowCaption)
	{
		// Init glfw
		if (!glfwInit())
			std::cout << "GLFW init error" << std::endl;
		m_glfwWindow = glfwCreateWindow(a_windowSize.x, a_windowSize.y, a_windowCaption.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_glfwWindow);

		// Callbacks
		glfwSetWindowSizeCallback(m_glfwWindow, window_size_callback);

		glfwSetWindowUserPointer(m_glfwWindow, this);

		glfwSwapInterval(0); 
		glViewport(0, 0, a_windowSize.x, a_windowSize.y);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_glfwWindow, true);
	}

	void Window::Clear()
	{
		Clear(math::Vector4(0, 0, 0, 0));
	}

	void Window::Clear(const math::Vector4 a_clearColor)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(a_clearColor.x, a_clearColor.y, a_clearColor.z, a_clearColor.w);
	}

	void Window::Display()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_glfwWindow);
	}

	const bool Window::IsOpen()
	{
		return !glfwWindowShouldClose(m_glfwWindow);
	}

	const GLFWwindow * Window::GetGLFWwindow()
	{
		return m_glfwWindow;
	}

	void window_size_callback(GLFWwindow * window, int width, int height)
	{
		glViewport(0, 0, width, height);

		Window* temp = (Window*)glfwGetWindowUserPointer(window);
		temp->owner->WindowResized(width, height);
	}

}
}