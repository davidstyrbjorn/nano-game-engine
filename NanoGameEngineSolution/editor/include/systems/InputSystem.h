#pragma once

#include"EditorSystem.h"

#include<deque>
#include<math\Vector2.h>

struct GLFWwindow;

namespace nano { namespace editor {  

	enum InputEventType {
		KEY_PRESSED,
		KEY_HOLD,
		MOUSE_PRESSED,
		MOUSE_HOLD,
		MOUSE_RELEASE
	};

	struct InputEvent {
		InputEventType type;
		int key;
	};

	class InputSystem : public EditorSystem<InputSystem> {
		friend class EditorSystem<InputSystem>;
	private:
		std::deque<InputEvent> m_polledEvents; // list for current frames polled events

		// Mouse 
		bool m_lmbDown = false, m_rmbDown = false;
		math::Vector2 m_mousePosition;

	private:
		// Private contructor (singleton)
		InputSystem() { }

	public:

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
		// Mouse position
		math::Vector2& GetMousePosition();
		void SetMousePosition(const math::Vector2 &a_pos);

		// GLFW callback functions
		friend static void character_callback(GLFWwindow* window, unsigned int codepoint);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

} }