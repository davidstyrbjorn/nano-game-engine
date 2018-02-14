#include"../include/systems/LevelParserSystem.h"
#include"../include/systems/RendererSystem.h"

#include<graphics\Simple_Renderer.h>
#include<graphics\Camera.h>

#include<fstream>
#include"SerializerAPI.h"

namespace nano { namespace editor { 

	LevelParserSystem* LevelParserSystem::_instance = nullptr;

	LevelParserSystem* LevelParserSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new LevelParserSystem();
		return _instance;
	}

	std::string LevelParserSystem::GetLevelStringFromFile(const char* a_folderPath)
	{
		return m_levelString;
	}

	void LevelParserSystem::ParseCurrentLevelToFile(const char* a_folderPath)
	{
		// TODO: 2018/13/02
		// Parse every entity from the world into the level text file
		// Parse every config-thing i.e; background-color, camera-stuff etc
		
		nano::OpenOutputFile(a_folderPath, OpenMode::TRUNCATE);

		// This is where we parse the entire fucking level into a text file with the correct format
		nano::WriteToFile("[LEVEL_CONFIG]", true);
		std::string camPosString = "cam_pos " + std::to_string(RendererSystem::Instance()->GetSimpleRenderer().GetCamera()->GetPosition().x) + ", " + std::to_string(RendererSystem::Instance()->GetSimpleRenderer().GetCamera()->GetPosition().y);
		nano::WriteToFile(camPosString);
		
		nano::CloseOutputFile();
	}

	void LevelParserSystem::Start()
	{

	}

	void LevelParserSystem::Quit()
	{
		m_levelString.clear();
	}

} }