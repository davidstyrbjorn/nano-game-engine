#include"../include/graphics/Window.h"

#include"../include/math/Vector2.h"
#include"../include/CoreConfig.h"

#include<GLFW\glfw3.h>

#include"../include/CoreConfig.h"

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

		//glfwSwapInterval(0); // @ what does this do vs not doing it?
		glViewport(0, 0, a_windowSize.x, a_windowSize.y);
		
		config = CoreConfig::Instance();
		config->SetWindowSize(a_windowSize);
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
		glClearColor(config->GetBackgroundColor().x, config->GetBackgroundColor().y, config->GetBackgroundColor().y, 1);
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
		CoreConfig::Instance()->SetWindowSize(math::Vector2(width, height));
	}

}
}