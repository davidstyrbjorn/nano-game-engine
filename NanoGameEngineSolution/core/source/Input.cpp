#include"../include/Input.h"

#include<GLFW\glfw3.h>

#include<iostream>

namespace nano {

	Input* Input::_instance = nullptr;

	Input * Input::Instance()
	{
		if (_instance == nullptr) {
			_instance = new Input();
		}
		return _instance;
	}

	Input::Input()
	{

	}

	void Input::SetCallbacks()
	{
		glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
	}

	void Input::FlushEvents()
	{
		m_eventQueue.clear();
	}

	bool Input::IsKeyDown(int a_key)
	{
		return m_keysDown[a_key];
	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		Input* _temp = Input::Instance();
		_temp->m_keysDown[key] = action != GLFW_RELEASE;

		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			Event _event;
			_event.key = key;
			if (action == GLFW_PRESS)
				_event.type = EventType::KEY_PRESSED;
			else if (action == GLFW_REPEAT)
				_event.type = EventType::KEY_HOLD;

			_temp->m_eventQueue.push_back(_event);
		}
	}

	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			Event _event;
			_event.key = button;
			if (action == GLFW_PRESS)
				_event.type = EventType::MOUSE_PRESSED;
			else if (action == GLFW_REPEAT)
				_event.type = EventType::MOUSE_HOLD;

			Input* _temp = Input::Instance();
			_temp->m_eventQueue.push_back(_event);
		}
	}

}