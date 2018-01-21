#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>

#include<GLFW\glfw3.h>

// OpenAL
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
#include"include\ecs\components\SoundComponent.h"

// OpenGL
#include"include\opengl\NanoOpenGL.h"
#include"include\opengl\IndexBuffer.h"
#include"include\opengl\VertexArrayObject.h"
#include"include\opengl\VertexBuffer.h"

// Sound
#include"include\sound\SoundBuffer.h"
#include"include\sound\SoundSource.h"
#include"include\sound\SoundContextDevice.h"

// Other
#include"include\Random.h"
#include"include\Clock.h"
#include"include\CoreConfig.h"

using namespace nano;

int main()
{
	CoreConfig::Instance()->SetShaderPaths("../../vertex.txt", "../../fragment.txt");

	nano::graphics::Window window(nano::math::Vector2(800, 600), "Save it");

	glewInit();
	
	openal::ContextDevice contextDevice;
	contextDevice.CreateDevice();
	contextDevice.CreateContext();

	graphics::SimpleRenderer renderer;

	nano::Input *inputObject = nano::Input::Instance();
	inputObject->SetCallbacks();

	ecs::Entity* entity = new ecs::Entity("test");
	entity->AddComponent(new ecs::TriangleComponent(math::Vector2(100, 100), math::Vector4(1, 0, 0, 1)));

	ecs::Entity* entity2 = new ecs::Entity("test2");
	entity2->AddComponent(new ecs::RectangleComponent(math::Vector2(50, 50), math::Vector4(0, 0, 1, 1)));
	entity2->AddComponent(new ecs::SoundComponent("D:\\temp\\sound.wav"));

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
					entity2->GetComponent<ecs::SoundComponent>()->GetSource()->Play();
				}
			}
		}
		if (inputObject->IsKeyDown(NANO_KEY_D))
			renderer.m_camera->Translate(math::Vector2(1.5f, 0));
		if (inputObject->IsKeyDown(NANO_KEY_A))
			renderer.m_camera->Translate(math::Vector2(-1.5f, 0));
		if (inputObject->IsKeyDown(NANO_KEY_W))
			renderer.m_camera->Translate(math::Vector2(0, -1.5f));
		if (inputObject->IsKeyDown(NANO_KEY_S))
			renderer.m_camera->Translate(math::Vector2(0, 1.5f));

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

	delete entity;
	delete entity2;
	delete entity3;

	return 0;
}