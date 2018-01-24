#pragma once

#include"../include/systems/InputSystem.h"

#include<GLFW\glfw3.h>

#include"../include/DearImGui/imgui.h"
#include"../include/DearImGui/imgui_glfw.h"

namespace nano { namespace editor {

	InputSystem* InputSystem::_instance = nullptr;
	InputSystem* InputSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new InputSystem();
		return _instance;
	}

	void InputSystem::Start()
	{
		// Set the GLFW callback functions
		/*
		Callbacks used in DearImGui!
		glfwSetMouseButtonCallback(window, ImGui_ImplGlfwGL3_MouseButtonCallback);
		glfwSetKeyCallback(window, ImGui_ImplGlfwGL3_KeyCallback);
		glfwSetCharCallback(window, ImGui_ImplGlfwGL3_CharCallback);
		*/
		glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
		glfwSetCharCallback(glfwGetCurrentContext(), character_callback);
	}

	void InputSystem::Update()
	{

	}

	void InputSystem::FlushEvents()
	{
		m_polledEvents.clear();
	}

	std::deque<InputEvent>& InputSystem::GetPolledEvents()
	{
		return m_polledEvents;
	}

	void InputSystem::Quit()
	{

	}
}

	// Static glfw callback functions

	void editor::character_callback(GLFWwindow * window, unsigned int codepoint)
	{
		// Calling for imgui
		ImGui_ImplGlfwGL3_CharCallback(window, codepoint);
	}

	void editor::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		// Calling for imgui
		ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);

		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			InputSystem* temp = InputSystem::Instance();

			// Create the event
			InputEvent _event;
			_event.key = key;
			if (action == GLFW_PRESS) _event.type = InputEventType::KEY_PRESSED;
			else					  _event.type = InputEventType::KEY_HOLD;

			// Add the event to the polled events list
			temp->m_polledEvents.push_back(_event);
		}
	}

	void editor::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		// Calling for imgui
		ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);

		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			InputSystem* temp = InputSystem::Instance();

			// Create the event
			InputEvent _event;
			_event.key = button;
			if (action == GLFW_PRESS) _event.type = InputEventType::MOUSE_PRESSED;
			else				      _event.type = InputEventType::MOUSE_HOLD;

			// Add the event to the polled events list
			temp->m_polledEvents.push_back(_event);
		}
	}

}