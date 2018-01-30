#include"../include/ecs/Entity.h"

#include"../include/ecs/Component.h"
#include"../include/ecs/components/TransformComponent.h"

namespace nano { namespace ecs {

	Entity::Entity()
	{
		m_id = "unnamed";
		m_transform = new ecs::Transform();
		m_transform->SetEntityOwner(this);
	}

	Entity::Entity(const std::string & a_id)
	{
		m_id = a_id;
		m_transform = new ecs::Transform();
		m_transform->SetEntityOwner(this);
	}

	Entity::Entity(const char * a_id)
	{
		m_id = a_id;
		m_transform = new ecs::Transform();
		m_transform->SetEntityOwner(this);
	}

	Entity::~Entity()
	{
		// pointer to m_renderableComponent does not need to be freed
		// it will be freed afer we're done freeing every component in m_componentsBag!
		for (std::vector<Component*>::iterator it = m_componentsBag.begin(); it != m_componentsBag.end(); ++it) {
			delete (*it);
		}
		m_componentsBag.clear();
	}

	Component* Entity::AddComponent(Component * a_componentToAdd)
	{
		a_componentToAdd->SetEntityOwner(this);
		m_componentsBag.push_back(a_componentToAdd);

		// Check if a_componentToAdd was a renderable component
		if (dynamic_cast<graphics::Renderable*>(a_componentToAdd) != nullptr) {
			// It was wow! set our renderable component pointer to this 
			m_renderableComponent = dynamic_cast<graphics::Renderable*>(a_componentToAdd);
		}

		a_componentToAdd->Init();

		return a_componentToAdd;
	}

	void Entity::Start()
	{
		for (Component* _component : m_componentsBag) {
			if(_component->GetState() == ECSStates::ACTIVE)
				_component->Start();
		}
	}

	void Entity::Update()
	{
		for (Component* _component : m_componentsBag) {
			if (_component->GetState() == ECSStates::ACTIVE) {
				_component->Update();
			}
		}

		// Remove dead components
		std::vector<Component*>::iterator it;
		for (it = m_componentsBag.begin(); it != m_componentsBag.end(); ) {
			if ((*it)->GetState() == ECSStates::DESTROYED) {
				delete (*it);
				it = m_componentsBag.erase(it);
			}
			else {
				++it;
			}
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

	int Entity::GetEditorState()
	{
		return m_editorState;
	}

	graphics::Renderable * Entity::GetRenderableComponent()
	{
		return m_renderableComponent;
	}

	void Entity::SetID(const std::string & a_id)
	{
		m_id = a_id;
	}

	void Entity::SetState(const int a_state)
	{
		m_state = static_cast<ECSStates>(a_state);
	}

	void Entity::SetEditorState(const int a_state)
	{
		m_editorState = static_cast<ECSEditorStates>(a_state);
	}

	void Entity::SetRenderableComponent(graphics::Renderable * a_renderable)
	{
		m_renderableComponent = a_renderable;
	}

} } 