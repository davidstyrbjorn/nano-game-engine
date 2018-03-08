#include"../include/LevelSystem.h"

#include<iostream>

#include"../include/EngineConfig.h"
#include"../include/WindowSystem.h"
#include"../include/RendererSystem.h"
#include"../include/WorldSystem.h"

#include"../include/LevelParser.h"

namespace nano { namespace engine {

	void LevelSystem::shutdown()
	{
		std::cout << "Level system quit correctly" << std::endl;
	}

	void LevelSystem::start()
	{
		// Load the startup level 
		ParsedLevel level;
		LevelParser parser;
		std::string startupLevel = "resources\\levels\\" + EngineConfig::getInstance()->getProjectInfo().startupLevel + ".txt";
		if (!parser.GetParsedLevelFromFile(startupLevel.c_str(), level)) {
			// @TODO: startup level can't be loaded!
		}

		// Call on all the systems a level has been loaded
		WorldSystem::getInstance()->newLevel(level.entities);
		RendererSystem::getInstance()->newLevel(level.camPos, level.camSize);
		WindowSystem::getInstance()->newLevel(level.camSize);
	}

	void LevelSystem::update()
	{

	}

} }