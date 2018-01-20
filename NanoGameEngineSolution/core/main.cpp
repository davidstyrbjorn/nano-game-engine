#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>

#include<GLFW\glfw3.h>

// Math and graphics
#include"include\graphics\Shader.h"
#include"include\graphics\Window.h"
#include"include\math\MathInclude.h"
#include"include\Input.h"
#include"include\graphics\Simple_Renderer.h"

// ECS
#include"include\ecs\Entity.h"
#include"include\ecs\components\RectangleComponent.h"
#include"include\ecs\components\TriangleComponent.h"

// OpenGL
#include"include\opengl\NanoOpenGL.h"
#include"include\opengl\IndexBuffer.h"
#include"include\opengl\VertexArrayObject.h"
#include"include\opengl\VertexBuffer.h"

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
	
	//opengl::VertexArrayObject VAO;
	//VAO.Bind();
	
	// Triangl test
	//struct Vertex {
	//	math::Vector2 pos;
	//	math::Vector3 color;
	//};
	//Vertex triangle1[] = {
	//	{ math::Vector2(0,0),     math::Vector3(1,0,0) },
	//	{ math::Vector2(0,300),   math::Vector3(0,1,0) },
	//	{ math::Vector2(300,300), math::Vector3(0,0,1) },
	//};
	//
	//opengl::VertexBuffer VBO;
	//VBO.SetData((float*)&triangle1, sizeof(triangle1), GL_STATIC_DRAW);
	//VBO.Bind();
	//
	//VAO.EnableVertexAttribArray(0);
	//VAO.EnableVertexAttribArray(1);
	//VAO.SetVertexAttribPointer(0, 2, GL_FLOAT, sizeof(Vertex), nullptr);
	//VAO.SetVertexAttribPointer(1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//VAO.Unbind();

	//////////////////////////////////////////////

	graphics::SimpleRenderer renderer;

	nano::Input *inputObject = nano::Input::Instance();
	inputObject->SetCallbacks();

	ecs::Entity* entity = new ecs::Entity("test");
	entity->AddComponent(new ecs::TriangleComponent(math::Vector2(100, 100), math::Vector4(1, 0, 0, 1)));

	ecs::Entity* entity2 = new ecs::Entity("test2");
	entity2->AddComponent(new ecs::TriangleComponent(math::Vector2(50, 50), math::Vector4(0, 0, 1, 1)));

	entity2->Start();
	entity->Start();
	while (window.IsOpen()) 
	{
		window.Clear();
		renderer.Begin();

		// Process events
		for (nano::Event _event : inputObject->GetEvents()) {
			if (_event.type == nano::EventType::KEY_DOWN) {
				if (_event.key == GLFW_KEY_D) 
					entity->m_transform->position = math::Vector2(entity->m_transform->position.x + 20, 0);
				if(_event.key == GLFW_KEY_A)					
					entity->m_transform->position = math::Vector2(entity->m_transform->position.x - 20, 0);

			}
		}

		// Manual Upate
		entity->Update();
		entity2->Update();

		renderer.Submit(entity2->GetComponent<ecs::TriangleComponent>());
		renderer.Submit(entity->GetComponent<ecs::TriangleComponent>());

		renderer.Flush();
		inputObject->FlushEvents();

		window.Display();
	}

	return 0;
}