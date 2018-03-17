#pragma once

#include"../include/systems/InputSystem.h"

#include<GLFW\glfw3.h>

#include"../include/DearImGui/imgui.h"
#include"../include/DearImGui/imgui_glfw.h"

#include<InputDefinitions.h>

namespace nano { namespace editor {

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
		glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
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

	bool InputSystem::IsMouseButtonDown(int a_button)
	{
		if (a_button == NANO_MOUSE_BUTTON_LEFT)
			return m_lmbDown;
   else if (a_button == NANO_MOUSE_BUTTON_RIGHT)
			return m_rmbDown;
	}

	math::Vector2 & InputSystem::GetMousePosition() 
	{
		return m_mousePosition;
	}

	void InputSystem::SetMousePosition(const math::Vector2 & a_pos)
	{
		m_mousePosition = a_pos;
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
			static InputSystem* temp = InputSystem::getInstance();

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

		static InputSystem* temp = InputSystem::getInstance();
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {

			// Create the event
			InputEvent _event;
			_event.key = button;
			if (action == GLFW_PRESS) _event.type = InputEventType::MOUSE_PRESSED;
			else				      _event.type = InputEventType::MOUSE_HOLD;

			// Add the event to the polled events list
			temp->m_polledEvents.push_back(_event);

			// Mouse down logic, not mouse events
			if (action == GLFW_PRESS) {
				if (button == NANO_MOUSE_BUTTON_LEFT) 
					temp->m_lmbDown = true;
				if (button == NANO_MOUSE_BUTTON_RIGHT)
					temp->m_rmbDown = true;
			}
		}
		if (action == GLFW_RELEASE) {

			// Create mouse release event
			InputEvent _event;
			_event.type = InputEventType::MOUSE_RELEASE;
			_event.key = button;
			temp->m_polledEvents.push_back(_event);

			// Mouse down logic
			if (temp->m_lmbDown && button == NANO_MOUSE_BUTTON_LEFT)
				temp->m_lmbDown = false;
			if (temp->m_rmbDown && button == NANO_MOUSE_BUTTON_RIGHT)
				temp->m_rmbDown = false;
		}
	}

	void editor::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		static InputSystem *instance = InputSystem::getInstance();
		instance->SetMousePosition(math::Vector2(xpos, ypos));
	}

}