#include"n_Entity.h"

#include"../ecs/components/RectangleComponent.h"
#include"../ecs/components/SoundComponent.h"
#include"../ecs/components/SpriteComponent.h"
#include"../ecs/components/TriangleComponent.h"

namespace nano { namespace experimental { namespace ecs { 

	Entity::Entity(const std::string& a_name) {
		name = a_name;
		transform.position = math::Vector2(0, 0);
		transform.size = math::Vector2(0, 0);
	}

	bool Entity::addComponent(_ComponentTypes a_type)
	{
		switch (a_type) {
		case _ComponentTypes::RECTANGLE:
			m_components[m_numOfComponents] = nano::ecs::RectangleComponent();
			break;
		case _ComponentTypes::TRIANGLE:
			m_components[m_numOfComponents] = nano::ecs::TriangleComponent();
			break;
		case _ComponentTypes::SPRITE:
			m_components[m_numOfComponents] = nano::ecs::SpriteComponent();
			break;
		case _ComponentTypes::SOUND:
			m_components[m_numOfComponents] = nano::ecs::SoundComponent();
			break;
		// TODO: Fourway move & Script Component?
		}
		m_numOfComponents++;
	}

	nano::ecs::Component & Entity::getComponent(_ComponentTypes a_type)
	{
		// TODO: insert return statement here
	}


} } } 