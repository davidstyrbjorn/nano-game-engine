#include"../include/ecs/Entity.h"

#include"../include/ecs/Component.h"
#include"../include/ecs/components/TransformComponent.h"

#include"../include/ecs/components/RectangleComponent.h"
#include"../include/ecs/components/TriangleComponent.h"
#include"../include/ecs/components/SpriteComponent.h"
#include"../include/ecs/components/SoundComponent.h"

#include"../include/ecs/RenderableComponent.h"

namespace nano { namespace ecs {

	Transform * Entity::Transform()
	{
		return m_TranformComponent;
	}

	RenderableComponent * Entity::Renderable()
	{
		return m_RenderableComponent;
	}

	SoundComponent * Entity::SoundComponent()
	{
		return m_SoundComponent;
	}

	Entity::Entity()
	{
		m_id = "unnamed";

		// New
		m_TranformComponent = new ecs::Transform();
		m_TranformComponent->SetEntityOwner(this);
	}

	Entity::Entity(const std::string & a_id)
	{
		m_id = a_id;

		// New
		m_TranformComponent = new ecs::Transform();
		m_TranformComponent->SetEntityOwner(this);
	}

	Entity::~Entity()
	{
		// New
		delete m_TranformComponent;
		delete m_RenderableComponent;
		delete m_SoundComponent;
	}

	Component * Entity::AddComponent(_ComponentTypes a_type)
	{
		switch (a_type) {
		case _ComponentTypes::RECTANGLE_COMPONENT:
			m_RenderableComponent = new RectangleComponent();
			m_RenderableComponent->SetEntityOwner(this);
			m_RenderableComponent->Init();
			
			return m_RenderableComponent;
			break;
		case _ComponentTypes::TRIANGLE_COMPONENT:
			m_RenderableComponent = new TriangleComponent();
			m_RenderableComponent->SetEntityOwner(this);
			m_RenderableComponent->Init();

			return m_RenderableComponent;
			break;
		case _ComponentTypes::SPRITE_COMPONENT:
			m_RenderableComponent = new SpriteComponent();
			m_RenderableComponent->SetEntityOwner(this);
			m_RenderableComponent->Init();

			return m_RenderableComponent;
			break;
		case _ComponentTypes::SOUND_COMPONENT:
			m_SoundComponent = new ecs::SoundComponent();
			m_SoundComponent->SetEntityOwner(this);
			m_SoundComponent->Init();
			break;
		}
	}

	void Entity::RemoveComponent(_ComponentTypes a_type)
	{
		switch (a_type) {
		case _ComponentTypes::RECTANGLE_COMPONENT || _ComponentTypes::TRIANGLE_COMPONENT || _ComponentTypes::SPRITE_COMPONENT:
			delete m_RenderableComponent;
			m_RenderableComponent = nullptr;
			break;
		case _ComponentTypes::SOUND_COMPONENT:
			delete m_SoundComponent;
			m_SoundComponent = nullptr;
			break;
		}
	}

	void Entity::Start()
	{
		// Call start on components
		if (m_RenderableComponent != nullptr)
			m_RenderableComponent->Start();
		if (m_SoundComponent != nullptr)
			m_SoundComponent->Start();
	}

	void Entity::Update()
	{
		// Call update on components 

		// Renderable Component
		if (m_RenderableComponent != nullptr) {
			m_RenderableComponent->Update();
		}
		// Sound Component
		if (m_SoundComponent != nullptr) {
			m_SoundComponent->Update();
		}
	}

	void Entity::FixedUpdate()
	{
		// Call fixed update on components

		// Renderable Component
		if (m_RenderableComponent != nullptr) {
			m_RenderableComponent->FixedUpdate();
		}
		// Sound Component
		if (m_SoundComponent != nullptr) {
			m_SoundComponent->FixedUpdate();
		}
	}

	std::string Entity::GetID()
	{
		return m_id;
	}

	std::string Entity::GetIDReference()
	{
		return m_id;
	}

	int Entity::GetState()
	{
		return m_state;
	}

	void Entity::SetID(const std::string & a_id)
	{
		m_id = a_id;
	}

	void Entity::SetState(const int a_state)
	{
		m_state = static_cast<ECSStates>(a_state);
	}

} } 