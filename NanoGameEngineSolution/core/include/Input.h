#pragma once

#include<deque>

struct GLFWwindow;

namespace nano {

	enum EventType {
		KEY_PRESSED,
		KEY_HOLD, 
		MOUSE_PRESSED,
		MOUSE_HOLD
	};

	struct Event {
		EventType type;
		int key;
	};

	class Input {
	private:
		std::deque<Event> m_eventQueue;

	private:
		// Singleton
		Input();

		// The sole intance of this class
		static Input* _instance;

	public:
		// The way to get access to the sole instance
		static Input* Instance();

		// Sets the callbacks
		void SetCallbacks();

		// Returns the event list
		const std::deque<Event>& GetEvents() { return m_eventQueue; }

		// Flushes all the current events inside the event system
		void FlushEvents();

		// GLFW callback functions
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	};
	
}