#include"../include/InputSystem.h"

#include<GLFW\glfw3.h>

namespace nano { namespace engine {

	void InputSystem::shutdown()
	{
		glfwSetCharCallback(glfwGetCurrentContext(), nullptr);
		glfwSetKeyCallback(glfwGetCurrentContext(), nullptr);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), nullptr);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), nullptr);
		glfwSetWindowUserPointer(glfwGetCurrentContext(), nullptr);

		std::cout << "Input system quti correctly" << std::endl;
	}

	void InputSystem::start()
	{
		glfwSetCharCallback(glfwGetCurrentContext(), character_callback);
		glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
		glfwSetWindowUserPointer(glfwGetCurrentContext(), this);
	}

	void InputSystem::update()
	{

	}

	void InputSystem::flushEvents()
	{
		m_polledEvents.clear();
	}

	std::deque<InputEvent>& InputSystem::getPolledEvents()
	{
		return m_polledEvents;
	}

	void character_callback(GLFWwindow * window, unsigned int codepoint)
	{

	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		InputSystem* inputSys = (InputSystem*)glfwGetWindowUserPointer(glfwGetCurrentContext());

		InputEvent inputEvent;
		inputEvent.key = key;
		if (action == GLFW_PRESS) inputEvent.type = INPUT_TYPE::KEY_PRESSED;
		else if (action == GLFW_RELEASE) inputEvent.type = INPUT_TYPE::KEY_RELEASE;
		else if (action == GLFW_REPEAT) inputEvent.type = INPUT_TYPE::KEY_HOLD;

		inputSys->m_polledEvents.push_back(inputEvent);
	}

	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		InputSystem* inputSys = (InputSystem*)glfwGetWindowUserPointer(glfwGetCurrentContext());

		InputEvent inputEvent;
		inputEvent.key = button;
		if (action == GLFW_PRESS) inputEvent.type = INPUT_TYPE::MOUSE_PRESSED;
		else if (action == GLFW_RELEASE) inputEvent.type = INPUT_TYPE::MOUSE_RELEASE;

		inputSys->m_polledEvents.push_back(inputEvent);
	}

	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
	}

} }