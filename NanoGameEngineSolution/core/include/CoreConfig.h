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
		// Window
		math::Vector2 s_windowSize;
		math::Vector3 s_backgroundColor = math::Vector3(0.2f, 0.2f, 0.2f);

		// Renderer
		std::string m_vertexShaderPath, m_fragmentShaderPath;

	public:
		// Window
		void SetWindowSize(const math::Vector2& a_windowSize);
		const math::Vector2 GetWindowSize();
		void SetBackgroundColor(const math::Vector3& a_color);
		const math::Vector3 GetBackgroundColor();
		
		// Renderer
		void SetShaderPaths(std::string a_vertex, std::string a_fragment);
		std::array<std::string, 2> GetShaderPaths();
	};
}