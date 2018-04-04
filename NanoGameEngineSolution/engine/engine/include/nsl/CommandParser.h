#pragma once

#include<ecs\Entity.h>
#include"nsl_definitions.h"

#include"../InputSystem.h"
#include"../LevelParser.h"
#include"../WorldSystem.h"

namespace nano { namespace engine {

	void moveCommand(ecs::Entity* entity, int xDir, int yDir, float speed) 
	{
		// Move the given entity with the given direction and speed 
		entity->m_transform->move(math::Vector2(xDir, yDir), speed);
	}

	void setPositionCommand(ecs::Entity* entity, float x, float y) 
	{
		// Set position
		entity->m_transform->position = math::Vector2(x, y);
	}

	void setSizeCommand(ecs::Entity* entity, float width, float height) 
	{
		// Set size
		entity->m_transform->size = math::Vector2(width, height);
	}

	void destroyCommand(std::string args)
	{
		std::cout << "destroy called with " << args << std::endl;
	}

	void createCommand(std::string args)
	{
		// Format: ($name)
		int start = args.find('$') + 1;
		int end = args.length() - 1;
		std::string temp = args.substr(start, end - start);
		// Use the level parser to get the given entity
		static LevelParser lp;
		std::string loc = "resources\\assets\\" + temp + ".txt";
		ecs::Entity* babyEntity = lp.getParsedEntityFromFile(loc.c_str());
		WorldSystem::getInstance()->addEntity(babyEntity);

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