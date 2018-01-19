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
	}

	void Input::FlushEvents()
	{
		m_eventQueue.clear();
	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			Event _event;
			_event.key = key;
			_event.type = static_cast<EventType>(action);

			Input* _temp = Input::Instance();
			_temp->m_eventQueue.push_back(_event);
		}
	}

}