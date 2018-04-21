#include"../include/ecs/Entity.h"

#include"../include/ecs/Component.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	Transform * Entity::Transform()
	{
		return m_TranformComponent;
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
		// pointer to m_renderableComponent does not need to be freed
		// it will be freed afer we're done freeing every component in m_componentsBag!
		///////////// OLD ///////////////
		//for (std::vector<Component*>::iterator it = m_componentsBag.begin(); it != m_componentsBag.end(); ++it) {
		//	delete (*it);
		//}
		//m_componentsBag.clear();
		//
		//delete m_transform;

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
			
			return m_RenderableComponent;
			break;
		case _ComponentTypes::TRIANGLE_COMPONENT:
			m_RenderableComponent = new TriangleComponent();
			break;
		case _ComponentTypes::SPRITE_COMPONENT:
			m_RenderableComponent = new SpriteComponent();
			break;
		}
	}

	void Entity::Start()
	{
		if (m_RenderableComponent != nullptr)
			m_RenderableComponent->Start();
	}

	void Entity::Update()
	{
		
	}

	void Entity::FixedUpdate()
	{
		
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