#pragma once

#include<graphics\GraphicsInclude.h>

namespace nano { namespace editor { 

	class EditorWindow : public graphics::Window {
	public:
		EditorWindow();

		// Gets called on window resize
		//void WindowResized(const math::Vector2& a_newSize) override;
	};

} }