#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>

#include<GLFW\glfw3.h>

#include"include\graphics\Shader.h"
#include"include\graphics\Window.h"
#include"include\math\MathInclude.h"
#include"include\Input.h"

#include"include\ecs\Component.h"
#include"include\ecs\test.h"
#include"include\ecs\Entity.h"

using namespace nano;

int main()
{
	nano::graphics::Window window(nano::math::Vector2(500, 500), "Save it");

	glewInit();
	glewExperimental = true;
	
	// Testing the shader
	nano::graphics::Shader* shader = new nano::graphics::Shader(std::string("D:\\NanoGameEngine\\NanoGameEngine\\vertex.txt"), std::string("D:\\NanoGameEngine\\NanoGameEngine\\fragment.txt"));
	shader->Bind();
	shader->SetUniformMat4f("projection_matrix", nano::math::Matrix4x4::Orthographic(0, 500, 500, 0, -1, 1));
	
	// Triangle render test
	float vertex_data[] = {
		0, 0,
		0, 300,
		300, 300
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	nano::Input *inputObject = nano::Input::Instance();
	inputObject->SetCallbacks();

	ecs::Entity* entity = new ecs::Entity("test");
	std::cout << entity->GetID() << std::endl;
	entity->AddComponent(new ecs::TestComponent());

	entity->Start();
	while (window.IsOpen()) 
	{
		window.Clear();

		// Process events
		for (nano::Event _event : inputObject->GetEvents()) 
			if (_event.type == nano::EventType::KEY_DOWN) 
				if (_event.key == GLFW_KEY_SPACE) 
					if(entity->GetComponent<ecs::TestComponent>() != nullptr)
						entity->GetComponent<ecs::TestComponent>()->SetState(ecs::ECSStates::DESTROYED);

		// Omg this if-stack is amazing

		// Test update entities
		entity->Update();

		shader->Bind();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shader->Unbind();

		inputObject->FlushEvents();
		window.Display();
	}

	return 0;
}