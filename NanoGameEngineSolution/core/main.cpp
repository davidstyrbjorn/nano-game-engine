#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>

#include"include\graphics\Shader.h"
#include"include\graphics\Window.h"
#include"include/math/MathInclude.h"

int main()
{

	nano::graphics::Window window(nano::math::Vector2(500, 500), "Save it");

	glewInit();
	glewExperimental = true;
	
	float vertex_data[] = {
		0, 0,
		0, 300,
		300, 300
	};

	nano::graphics::Shader* shader = new nano::graphics::Shader(std::string("C:\\NanoGameEngine_folder\\vertex.txt"), std::string("C:\\NanoGameEngine_folder\\fragment.txt"));
	shader->Bind();
	shader->SetUniformMat4f("projection_matrix", nano::math::Matrix4x4::Orthographic(0, 500, 500, 0, -1, 1));

	GLuint vbo;
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	while (window.IsOpen()) 
	{
		window.Clear();

		shader->Bind();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shader->Unbind();

		window.Display();
	}

	return 0;
}