#pragma once

#include<math\Vector2.h>

namespace nano { namespace editor { 

class EditorConfig {

private:
	// Singleton closure
	EditorConfig() { }
	static EditorConfig* _instance;

	math::Vector2 m_windowSize;

public:
	// Singleton connection
	static EditorConfig* Instance();

	const math::Vector2 getWindowSize();
	void setWindowSize(const math::Vector2& a_windowSize);

};

} } 