#pragma once

#include<string>
#include"../Core.h"
#include<map>

namespace nano {
	namespace math {
		class Vector2;
		class Vector3;
		class Vector4;
		class Matrix4x4;
	}
}

namespace nano { namespace graphics { 

	class Shader {
	public:
		// Default Constructor
		Shader();

		// Constructor with path to shader file
		Shader(std::string a_vertexShaderPath, std::string a_fragmentShaderPath);

		// Compiles the shader
		void CompileShader();

		// OpenGL shader bind and unbind
		void Bind();
		void Unbind();

		// Uniform setters
		void SetUniform1f(const char* a_name, float a_value);
		void SetUniform1fv(const char* a_name, int a_count, float* a_value);
		void SetUniform2f(const char* a_name, const math::Vector2 &a_vec2);
		void SetUniform3f(const char* a_name, const math::Vector3 &a_vec3);
		void SetUniform4f(const char* a_name, const math::Vector4 &a_vec4);
		void SetUniformMat4f(const char* a_name, const math::Matrix4x4 &a_matrix);

		float GetUniform1f(const char* a_name);
		math::Vector2& GetUniform2f(const char* a_name);
		math::Vector3& GetUniform3f(const char* a_name);
		math::Vector4& GetUniform4f(const char* a_name);

	private:
		bool didCompile(GLuint a_shader, std::string &a_errorMessage);
		GLint getUniformLocation(const char* a_name);

	private:
		// OpenGL handle to the shaders program
		GLuint m_shaderProgram;
		// Caching the uniform location to save performance 
		std::map<const char*, GLint> m_uniformMap;
		
		// The actual string text representation of the shader file to be compiled
		std::string m_vertexShaderData;
		std::string m_fragmentShaderData;
	};

} } 