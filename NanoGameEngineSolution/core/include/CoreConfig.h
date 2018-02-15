#pragma once

#include"math\Vector2.h"
#include"math\Vector3.h"
#include"graphics\Camera.h"

#include<string>
#include<array>

namespace nano {
	class CoreConfig {
	private:
		// Private constructor - singleton
		CoreConfig() {} 

		// The one sole instance
		static CoreConfig *_instance;

	public:
		// Singleton connection
		static CoreConfig* Instance();

	private:
		// Core
		unsigned int gFps;

		// Window
		math::Vector2 gWindowSize;
		math::Vector3 gBackgroundColor = math::Vector3(0.2f, 0.2f, 0.2f);

		// Renderer
		std::string gVertexShaderPath, gFragmentShaderPath;
		const char* gErrorTexturePath;

	public:
		// Core
		void SetFPS(unsigned int a_fps);
		unsigned int GetFPS();

		// Window
		void SetWindowSize(const math::Vector2& a_windowSize);
		const math::Vector2 GetWindowSize();
		void SetBackgroundColor(const math::Vector3& a_color);
		const math::Vector3 GetBackgroundColor();
		
		// Renderer
		void SetShaderPaths(std::string a_vertex, std::string a_fragment);
		std::array<std::string, 2> GetShaderPaths();
		void SetErrorTexturePath(const char* a_path);
		const char* GetErrorTexturePath();
	};
}