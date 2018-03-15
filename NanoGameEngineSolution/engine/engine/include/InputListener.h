#pragma once

namespace nano { namespace engine {

	// Abstract class for other classes that want to be notified when something is pressed
	class InputListener {
	public:
		virtual void onKeyPressed(int a_key) { }
		virtual void onMousePressed(int a_key) { }
		virtual void onMouseRelease(int a_key) { }
		virtual void onKeyReleased(int a_key) { }
	};

} }