#pragma once

#include<iostream>
#include"../ecs/Component.h"
#include"../ecs/components/TransformComponent.h"

#include"n_ComponentTypes.h"

namespace nano { namespace experimental { namespace ecs {  

	/*
	Idea: Get rid of ugly pointers everywhere, try to keep entity component on stack
	since I know the components beforehand I can manually create methods for adding/deleting components
	*/

	class Entity {
	public:
		Entity(const std::string &a_name);

		bool addComponent(_ComponentTypes a_type);
		nano::ecs::Component& getComponent(_ComponentTypes a_type);
		//bool removeComponent(_ComponentTypes a_type);
		nano::ecs::Transform transform;

		nano::ecs::Component slotToComponent();


	private:
		std::string name;
		nano::ecs::Component m_components[NUM_OF_COMPONENTS];
		int m_numOfComponents = 0;
	};

} } } 