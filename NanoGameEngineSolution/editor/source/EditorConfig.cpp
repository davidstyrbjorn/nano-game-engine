#include"../include/systems/EditorConfig.h"

namespace nano { namespace editor { 

	EditorConfig* EditorConfig::_instance = nullptr;

	EditorConfig* EditorConfig::Instance() {
		if (_instance == nullptr) {
			_instance = new EditorConfig();
		}
		return _instance;
	}

	const math::Vector2 EditorConfig::getWindowSize()
	{
		return m_windowSize;
	}

	void EditorConfig::setWindowSize(const math::Vector2 & a_windowSize)
	{
		m_windowSize = a_windowSize;
	}

} } 