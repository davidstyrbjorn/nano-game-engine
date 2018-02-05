#include"../include/CoreConfig.h"

namespace nano {

	CoreConfig* CoreConfig::_instance = nullptr;

	CoreConfig * CoreConfig::Instance()
	{
		if (_instance == nullptr) {
			_instance = new CoreConfig();
		}
		return _instance;
	}

	void CoreConfig::SetWindowSize(const math::Vector2 & a_windowSize)
	{
		s_windowSize = a_windowSize;
	}

	const math::Vector2 CoreConfig::GetWindowSize()
	{
		return s_windowSize;
	}

	void CoreConfig::SetBackgroundColor(const math::Vector3 & a_color)
	{
		s_backgroundColor = a_color;
	}

	const math::Vector3 CoreConfig::GetBackgroundColor()
	{
		return s_backgroundColor;
	}

	void CoreConfig::SetShaderPaths(std::string a_vertex, std::string a_fragment)
	{
		m_vertexShaderPath = a_vertex;
		m_fragmentShaderPath = a_fragment;
	}

	std::array<std::string, 2> CoreConfig::GetShaderPaths()
	{
		return { m_vertexShaderPath, m_fragmentShaderPath };
	}

	void CoreConfig::SetErrorTexturePath(const char * a_path)
	{
		m_errorTexturePath = a_path;
	}

	const char * CoreConfig::GetErrorTexturePath()
	{
		return m_errorTexturePath;
	}

}