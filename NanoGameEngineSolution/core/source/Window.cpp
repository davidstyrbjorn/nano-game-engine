#include"../include/graphics/Window.h"

#include"../include/math/Vector2.h"
#include"../include/CoreConfig.h"

#include<GLFW\glfw3.h>

namespace nano { namespace graphics {

	Window::Window(const math::Vector2 & a_windowSize, const std::string & a_windowCaption)
	{
		CoreConfig::Instance()->SetWindowSize(a_windowSize);

		// Init glfw
		if (!glfwInit())
			std::cout << "GLFW init error" << std::endl;

		m_glfwWindow = glfwCreateWindow(a_windowSize.x, a_windowSize.y, a_windowCaption.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_glfwWindow);

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
		glClear(GL_COLOR_BUFFER_BIT);
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

	const math::Vector2 & Window::GetWindowSize()
	{
		int _x, _y;
		glfwGetWindowSize(m_glfwWindow, &_x, &_y);
		return math::Vector2(_x, _y);
	}

	const GLFWwindow * Window::GetGLFWwindow()
	{
		return m_glfwWindow;
	}

} }