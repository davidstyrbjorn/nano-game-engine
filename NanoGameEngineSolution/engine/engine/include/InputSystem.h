#pragma once

#include"EngineSystemBase.h"

#include<math\Vector2.h>
#include<deque>
#include<vector>

struct GLFWwindow;

namespace nano { namespace engine { 

	class InputListener;

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
		bool m_keys[1028];

		std::vector<InputListener*> m_inputListeners;

	public:
		void start() override;
		void update() override;
		void shutdown() override;		

		void flushEvents();
		std::deque<InputEvent> &getPolledEvents();
		bool isKeyDown(int a_keyCode) { return m_keys[a_keyCode]; }

		// Input listener methods
		void addInputListener(InputListener* a_inputListener);
		void removeInputListener(InputListener* a_inputListener);

		// GLFW callback functions
		friend static void character_callback(GLFWwindow* window, unsigned int codepoint);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

} }