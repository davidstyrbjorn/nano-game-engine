#pragma once

#include<deque>

struct GLFWwindow;

namespace nano {

	enum EventType {
		KEY_DOWN = 1,
		KEY_HOLD = 2
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
	};
	
}