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

	void CoreConfig::SetFPS(unsigned int a_fps)
	{
		gFps = a_fps;
	}

	unsigned int CoreConfig::GetFPS()
	{
		return gFps;
	}

	void CoreConfig::SetWindowSize(const math::Vector2 & a_windowSize)
	{
		gWindowSize = a_windowSize;
	}

	const math::Vector2 CoreConfig::GetWindowSize()
	{
		return gWindowSize;
	}

	void CoreConfig::SetBackgroundColor(const math::Vector3 & a_color)
	{
		gBackgroundColor = a_color;
	}

	const math::Vector3 CoreConfig::GetBackgroundColor()
	{
		return gBackgroundColor;
	}

	void CoreConfig::SetShaderPaths(std::string a_vertex, std::string a_fragment)
	{
		gVertexShaderPath = a_vertex;
		gFragmentShaderPath = a_fragment;
	}

	std::array<std::string, 2> CoreConfig::GetShaderPaths()
	{
		return { gVertexShaderPath, gFragmentShaderPath };
	}

	void CoreConfig::SetErrorTexturePath(const char * a_path)
	{
		gErrorTexturePath = a_path;
	}

	const char * CoreConfig::GetErrorTexturePath()
	{
		return gErrorTexturePath;
	}

}