#pragma once

#include"EditorSystem.h"

#include<deque>

struct GLFWwindow;

namespace nano { namespace editor {  

	enum InputEventType {
		KEY_PRESSED,
		KEY_HOLD,
		MOUSE_PRESSED,
		MOUSE_HOLD
	};

	struct InputEvent {
		InputEventType type;
		int key;
	};

	class InputSystem : EditorSystem {
	private:
		std::deque<InputEvent> m_polledEvents; // list for current frames polled events
		bool m_lmbDown = false, m_rmbDown = false;

	private:
		// Private contructor (singleton)
		InputSystem() { }

		// One sole instance
		static InputSystem* _instance;

	public:
		// Singleton connection
		static InputSystem* Instance();

		// Base class methods
		void Start() override;
		void Update() override;
		void Quit() override;

		// Flushes all the events currently inside m_polledEvents
		void FlushEvents();
		// Return this frames polled events
		std::deque<InputEvent>& GetPolledEvents();
		// m_rmbDown && m_lmbDown
		bool IsMouseButtonDown(int a_button);

		// GLFW callbacks
		// GLFW callback functions
		friend static void character_callback(GLFWwindow* window, unsigned int codepoint);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	};

} }