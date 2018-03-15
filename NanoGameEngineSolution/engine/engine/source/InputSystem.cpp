#include"../include/InputSystem.h"

#include<GLFW\glfw3.h>

#include"../include/InputListener.h"

namespace nano { namespace engine {

	void InputSystem::shutdown()
	{
		glfwSetCharCallback(glfwGetCurrentContext(), nullptr);
		glfwSetKeyCallback(glfwGetCurrentContext(), nullptr);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), nullptr);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), nullptr);

		std::cout << "Input system quit correctly" << std::endl;
	}

	void InputSystem::start()
	{
		glfwSetCharCallback(glfwGetCurrentContext(), character_callback);
		glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
	}

	void InputSystem::update()
	{
		for (InputEvent event : m_polledEvents) {
			if (event.type == INPUT_TYPE::KEY_PRESSED) {
				for (InputListener *il : m_inputListeners) {
					il->onKeyPressed(event.key);
				}
			}
			else if (event.type == INPUT_TYPE::KEY_RELEASE) {
				for (InputListener *il : m_inputListeners) {
					il->onKeyReleased(event.key);
				}
			}
			else if (event.type == INPUT_TYPE::MOUSE_PRESSED) {
				for (InputListener *il : m_inputListeners) {
					il->onMousePressed(event.key);
				}
			}
			else if (event.type == INPUT_TYPE::MOUSE_RELEASE) {
				for (InputListener *il : m_inputListeners) {
					il->onMouseRelease(event.key);
				}
			}
		}
	}

	void InputSystem::flushEvents()
	{
		m_polledEvents.clear();
	}

	std::deque<InputEvent>& InputSystem::getPolledEvents()
	{
		return m_polledEvents;
	}

	void InputSystem::addInputListener(InputListener * a_inputListener)
	{
		m_inputListeners.push_back(a_inputListener);
	}

	void InputSystem::removeInputListener(InputListener * a_inputListener)
	{
		std::vector<InputListener*> newList;
		for (InputListener *il : m_inputListeners) {
			if (il != nullptr)
				newList.push_back(il);
		}
		m_inputListeners = newList;
	}

	void character_callback(GLFWwindow * window, unsigned int codepoint)
	{

	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		InputSystem* inputSys = InputSystem::getInstance();

		InputEvent inputEvent;
		inputEvent.key = key;
		if (action == GLFW_PRESS)
		{
			inputSys->m_keys[key] = true;
			inputEvent.type = INPUT_TYPE::KEY_PRESSED;
		}
		else if (action == GLFW_RELEASE)
		{
			inputSys->m_keys[key] = false;
			inputEvent.type = INPUT_TYPE::KEY_RELEASE;
		}
		else if (action == GLFW_REPEAT) 
		{
			inputEvent.type = INPUT_TYPE::KEY_HOLD;
		}

		inputSys->m_polledEvents.push_back(inputEvent);
	}

	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		InputSystem* inputSys = InputSystem::getInstance();

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