#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>

#include<GLFW\glfw3.h>

#include<al.h>
#include<alc.h>

// Math and graphics
#include"include\graphics\Shader.h"
#include"include\graphics\Window.h"
#include"include\math\MathInclude.h"
#include"include\Input.h"
#include"include\InputDefinitions.h"
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

// Other
#include"include\Random.h"
#include"include\Clock.h"

using namespace nano;

int main()
{
	nano::graphics::Window window(nano::math::Vector2(800, 600), "Save it");

	glewInit();
	glewExperimental = true;
	
	// Testing the shader
	nano::graphics::Shader* shader = new nano::graphics::Shader(std::string("D:\\NanoGameEngine\\NanoGameEngine\\vertex.txt"), std::string("D:\\NanoGameEngine\\NanoGameEngine\\fragment.txt"));
	shader->Bind();
	shader->SetUniformMat4f("projection_matrix", nano::math::Matrix4x4::Orthographic(0, 800, 600, 0, -1, 1));
	
	graphics::SimpleRenderer renderer;

	nano::Input *inputObject = nano::Input::Instance();
	inputObject->SetCallbacks();

	ecs::Entity* entity = new ecs::Entity("test");
	entity->AddComponent(new ecs::TriangleComponent(math::Vector2(100, 100), math::Vector4(1, 0, 0, 1)));

	ecs::Entity* entity2 = new ecs::Entity("test2");
	entity2->AddComponent(new ecs::RectangleComponent(math::Vector2(50, 50), math::Vector4(0, 0, 1, 1)));

	ecs::Entity *entity3 = new ecs::Entity("test3");
	entity3->AddComponent(new ecs::RectangleComponent(math::Vector2(200, 100), math::Vector4(1, 0.5, 0.5, 1)));
	entity3->m_transform->position = math::Vector2(400, 400);

	entity3->Start();
	entity2->Start();
	entity->Start();
	while (window.IsOpen()) 
	{
		window.Clear();
		renderer.Begin();

		// Process events
		for (nano::Event _event : inputObject->GetEvents()) {
			if (_event.type == EventType::MOUSE_PRESSED) {
				if (_event.key == NANO_MOUSE_BUTTON_RIGHT) {
					std::cout << "Be Right Back" << std::endl;
				}
			}
			if (_event.type == nano::EventType::KEY_PRESSED) {
				if (_event.key == NANO_KEY_D) 
					entity->m_transform->position = math::Vector2(entity->m_transform->position.x + 20, 0);
				if(_event.key == NANO_KEY_A)					
					entity->m_transform->position = math::Vector2(entity->m_transform->position.x - 20, 0);
			}
		}

		// Manual Upate
		entity->Update();
		entity2->Update();
		entity3->Update();

		renderer.Submit(entity3->GetComponent<ecs::RectangleComponent>());
		renderer.Submit(entity2->GetComponent<ecs::RectangleComponent>());
		renderer.Submit(entity->GetComponent<ecs::TriangleComponent>());

		renderer.Flush();
		inputObject->FlushEvents();

		window.Display();
	}

	return 0;
}