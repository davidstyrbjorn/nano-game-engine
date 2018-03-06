#pragma once

#include"EngineSystemBase.h"

#include<math\Vector2.h>
#include<deque>

struct GLFWwindow;

namespace nano { namespace engine { 

	enum INPUT_TYPE {
		// Key
		KEY_PRESSED,
		KEY_HOLD,
		KEY_RELEASE,
		// Mouse 
		MOUSE_PRESSED,
		MOUSE_RELEASE
	};

	struct InputEvent {
		INPUT_TYPE type;
		int key;
	};

	class InputSystem : public EngineSystemBase<InputSystem> {
	friend class EngineSystemBase<InputSystem>;

	private:
		InputSystem() { }

		std::deque<InputEvent> m_polledEvents; // List of all the polled events (gets cleared each frame)
	
	public:
		void start() override;
		void update() override;
		void shutdown() override;		

		void flushEvents();
		std::deque<InputEvent> &getPolledEvents();

		// GLFW callback functions
		friend static void character_callback(GLFWwindow* window, unsigned int codepoint);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

} }