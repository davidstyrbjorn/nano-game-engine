#pragma once

#include<ecs\Entity.h>
#include"nsl_definitions.h"

#include"../InputSystem.h"

namespace nano { namespace engine {

	void moveCommand(ecs::Entity* entity, std::string args) 
	{
		// Get the number literals from the argument string
		float xLiteral = std::stof(args.substr(1, args.find_first_of(identifierSplit)));
		float yLiteral = std::stof(args.substr(args.find_first_of(identifierSplit) + 1, args.find_last_of(identifierSplit)));
		float speedLiteral = std::stof(args.substr(args.find_last_of(identifierSplit) + 1, args.length() - 1));
		// Move the given entity with the given direction and speed 
		entity->m_transform->move(math::Vector2(xLiteral, yLiteral), speedLiteral);
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