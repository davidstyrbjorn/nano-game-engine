#include"../include/systems/LevelParserSystem.h"

namespace nano { namespace editor { 

	LevelParserSystem* LevelParserSystem::_instance = nullptr;

	LevelParserSystem* LevelParserSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new LevelParserSystem();
		return _instance;
	}

	std::string LevelParserSystem::GetLevelString()
	{
		return m_levelString;
	}

	void LevelParserSystem::ParseCurrentLevelToString()
	{
		// TODO: 2018/13/02
		// Parse every entity from the world into the level text file
		// Parse every config-thing i.e; background-color, camera-stuff etc

	}

	void LevelParserSystem::Start()
	{

	}

	void LevelParserSystem::Quit()
	{
		m_levelString.clear();
	}

} }