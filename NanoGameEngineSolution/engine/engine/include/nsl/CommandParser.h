#pragma once

#include<ecs\Entity.h>
#include"nsl_definitions.h"

#include"../InputSystem.h"

namespace nano { namespace engine {

	void moveCommand(ecs::Entity* entity, int xDir, int yDir, float speed) 
	{
		// Move the given entity with the given direction and speed 
		std::cout << xDir << std::endl;
		std::cout << yDir << std::endl;
		std::cout << speed << std::endl;
		entity->m_transform->move(math::Vector2(xDir, yDir), speed);
	}

	void setPositionCommand(ecs::Entity* entity, std::string args) 
	{
		int identifierIndex = args.find(identifierSplit);
		float xLiteral = std::stof(args.substr(1, identifierIndex));
		float yLiteral = std::stof(args.substr(identifierIndex+1, args.length()-identifierIndex+1));
		entity->m_transform->position = math::Vector2(xLiteral, yLiteral);
	}

	void setSizeCommand(ecs::Entity* entity, std::string args) 
	{
		int identifierIndex = args.find(identifierSplit);
		float xLiteral = std::stof(args.substr(1, identifierIndex));
		float yLiteral = std::stof(args.substr(identifierIndex + 1, args.length() - identifierIndex + 1));
		entity->m_transform->size = math::Vector2(xLiteral, yLiteral);
	}

	void destroyCommand(std::string args)
	{
		std::cout << "destroy called with " << args << std::endl;
	}

	void createCommand(std::string args)
	{
		std::cout << "create called with " << args << std::endl;
	}

	bool isKeyDownExpressionTrue(std::string args) 
	{
		int keyCodeLiteral = std::stoi(args.substr(args.find('(') + 1, args.find(')')));
		static InputSystem* input = InputSystem::getInstance();
		if (input->isKeyDown(keyCodeLiteral)) {
			return true;
		}
		return false;
	}

	int getKeyCodeLiteralFromArg(std::string arg)
	{
		return std::stoi(arg.substr(arg.find('(') + 1, arg.find(')')));
	}

} }