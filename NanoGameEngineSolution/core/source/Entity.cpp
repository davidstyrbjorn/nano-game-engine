#include"../include/ecs/Entity.h"

#include"../include/ecs/Component.h"

namespace nano { namespace ecs {

	Entity::Entity()
	{
		m_id = "unnamed";
		m_transform = new ecs::Transform();
	}

	Entity::Entity(const std::string & a_id)
	{
		m_id = a_id;
		m_transform = new ecs::Transform();
	}

	Entity::Entity(const char * a_id)
	{
		m_id = a_id;
		m_transform = new ecs::Transform();
	}

	Entity::~Entity()
	{
		for (std::vector<Component*>::iterator it = m_componentsBag.begin(); it != m_componentsBag.end(); ++it) {
			delete (*it);
		}
		m_componentsBag.clear();
	}

	void Entity::AddComponent(Component * a_componentToAdd)
	{
		a_componentToAdd->SetEntityOwner(this);
		m_componentsBag.push_back(a_componentToAdd);
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