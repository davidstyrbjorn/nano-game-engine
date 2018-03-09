#pragma once

#include<ecs\Entity.h>

namespace nano { namespace engine {

	void moveCommand(ecs::Entity* entity, std::string args) 
	{
		// Get the number literals from the argument string
		float xLiteral = std::stof(args.substr(1, args.find(',')));
		float yLiteral = std::stof(args.substr(args.find(',') + 1, args.length() - 1));

		entity->m_transform->move(math::Vector2(xLiteral, yLiteral), 4);
	}

	void destroyCommand(std::string args)
	{

	}

	void createCommand(std::string args)
	{

	}

	

} }