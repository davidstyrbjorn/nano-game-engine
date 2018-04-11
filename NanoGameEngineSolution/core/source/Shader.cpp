#include"../include/graphics/Shader.h"

#include"../include/math/MathInclude.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include<fstream>
#include<vector>
#include<iostream>

namespace nano { namespace graphics { 

Shader::Shader()
{
	m_vertexShaderData = "";
	m_fragmentShaderData = "";
}

Shader::Shader(std::string a_vertexShaderPath, std::string a_fragmentShaderPath)
{
	std::ifstream vertexFile(a_vertexShaderPath);
	std::ifstream fragmentFile(a_fragmentShaderPath);
	if (!vertexFile.is_open() || !fragmentFile.is_open()) {
		// @ Throw error file is not open
		std::cout << "Could not open either fragment or vertex shader at given path" << std::endl;
	}

	// Get content from vertex shader file
	std::string line;
	while (std::getline(vertexFile, line)) {
		m_vertexShaderData += line + "\n";
	}

	line.clear();

	// Get content from fragment shader file
	while (std::getline(fragmentFile, line)) {
		m_fragmentShaderData += line + "\n";
	}

	CompileShader();
}

bool Shader::didCompile(GLuint a_shader, std::string &a_errorMessage)
{
	GLint _didCompile;
	glGetShaderiv(a_shader, GL_COMPILE_STATUS, &_didCompile);
	if (_didCompile == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(a_shader, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		GLchar infoLog[200];
		glGetShaderInfoLog(a_shader, maxLength, &maxLength, &infoLog[0]);
		a_errorMessage = infoLog;

		return false;
	}
	return true;
}

void Shader::CompileShader()
{
	glewInit();
	glewExperimental = true;

	// Create and compile the shaders using the m_vertexShaderData and m_fragmentShaderData
	GLuint m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSource = m_vertexShaderData.c_str();
	glShaderSource(m_vertexShader, 1, &vertexSource, 0);
	glCompileShader(m_vertexShader);
	std::string vertexCompileMessage = "";
	if (!didCompile(m_vertexShader, vertexCompileMessage)) {
		std::cout << vertexCompileMessage << "\n";
	}

	GLuint m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSource = m_fragmentShaderData.c_str();
	glShaderSource(m_fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(m_fragmentShader);
	std::string fragmentCompileMessage = "";
	if (!didCompile(m_fragmentShader, fragmentCompileMessage)) {
		std::cout << fragmentCompileMessage << "\n";
	}

	// Create shader program
	m_shaderProgram = glCreateProgram();

	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glLinkProgram(m_shaderProgram);

	glDetachShader(m_shaderProgram, m_vertexShader);
	glDetachShader(m_shaderProgram, m_fragmentShader);

	// Now that shaders are attatched to the program we can delete them
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}

GLint Shader::getUniformLocation(const char * a_name)
{
	if (m_uniformMap.find(a_name) == m_uniformMap.end()) {
		// a_name does not exists as uniform location
		m_uniformMap.insert(std::pair<const char*, GLint>(a_name, glGetUniformLocation(m_shaderProgram, a_name)));
	}
	return m_uniformMap.at(a_name);
}

void Shader::SetUniform1f(const char * a_name, float a_value)
{
	glUniform1f(getUniformLocation(a_name), a_value);
}

void Shader::SetUniform1fv(const char * a_name, int a_count, float * a_value)
{
	glUniform1fv(getUniformLocation(a_name), a_count, a_value);
}

void Shader::SetUniform2f(const char* a_name, const math::Vector2 & a_vec2)
{
	glUniform2f(getUniformLocation(a_name), a_vec2.x, a_vec2.y);
}

void Shader::SetUniform3f(const char * a_name, const math::Vector3 & a_vec3)
{
	glUniform3f(getUniformLocation(a_name), a_vec3.x, a_vec3.y, a_vec3.z);
}

void Shader::SetUniform4f(const char * a_name, const math::Vector4 & a_vec4)
{
	glUniform4f(getUniformLocation(a_name), a_vec4.x, a_vec4.y, a_vec4.z, a_vec4.w);
} 

void Shader::SetUniformMat4f(const char * a_name, const math::Matrix4x4 & a_matrix)
{
	glUniformMatrix4fv(getUniformLocation(a_name), 1, false, a_matrix.elements);
}

float Shader::GetUniform1f(const char * a_name)
{
	float *x = nullptr;
	glGetUniformfv(m_shaderProgram, getUniformLocation(a_name), x);
	return *x;
}

math::Vector2 & Shader::GetUniform2f(const char * a_name)
{
	return math::Vector2(0, 0);
}

math::Vector3 & Shader::GetUniform3f(const char * a_name)
{
	return math::Vector3(0, 0, 0);
}

math::Vector4 & Shader::GetUniform4f(const char * a_name)
{
	return math::Vector4(0, 0, 0, 0);
}

void Shader::Bind()
{
	glUseProgram(m_shaderProgram);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

} }  