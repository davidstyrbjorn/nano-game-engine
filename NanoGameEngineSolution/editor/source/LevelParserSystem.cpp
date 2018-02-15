#include"../include/systems/LevelParserSystem.h"
#include"../include/systems/RendererSystem.h"
#include<CoreConfig.h>
#include"../include/systems/WorldSystem.h"

#include<graphics\Simple_Renderer.h>
#include<graphics\Camera.h>
#include<ecs\Entity.h>
#include<graphics\Renderable.h>
#include<ecs\components\SpriteComponent.h>

#include<fstream>
#include"SerializerAPI.h"

#include<StringHelp.h>

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
		
		CoreConfig *config = CoreConfig::Instance();
		RendererSystem *renderSystem = RendererSystem::Instance();
		WorldSystem* world = WorldSystem::Instance();

		std::vector<ecs::Entity*> entitiesToSave = world->GetEntityList();

		nano::OpenOutputFile(a_folderPath, OpenMode::TRUNCATE);

		// This is where we parse the entire fucking level into a text file with the correct format

		// Level Config
		nano::WriteToFile("[LEVEL_CONFIG]", true);
		std::string camPosString = "cam_pos " + to_string_with_precision<float>(renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().x, 6) + ", " + to_string_with_precision<float>(renderSystem->GetSimpleRenderer().GetCamera()->GetPosition().y, 6);
		nano::WriteToFile(camPosString, true);
		std::string fpsString = "fps " + std::to_string(config->GetFPS());
		nano::WriteToFile(fpsString.c_str(), true);

		nano::InsertBlankLine();

		// Level Entities and their components
		nano::WriteToFile("[LEVEL_ENTITIES]", true);
		for (ecs::Entity* entity : entitiesToSave) {
			nano::WriteToFile("[ENTITY]", true);

			std::string entityIdString = "id " + entity->GetID();
			nano::WriteToFile(entityIdString.c_str(), true);
			// 1. Renderable, sound component, fourwaymove component

			nano::WriteToFile("renderable", true);
			graphics::Renderable* renderable = entity->GetRenderableComponent();
			if (renderable != nullptr) {
				// Vertex count
				std::string vertexCountString = "vertex_count " + std::to_string(renderable->GetVertexCount());
				nano::WriteToFile(vertexCountString.c_str(), true);

				// Color
				std::string colorString = "color " + renderable->GetColor().ToString();
				nano::WriteToFile(colorString.c_str(), true);

				// Texture path
				ecs::SpriteComponent *spriteComponent = entity->GetComponent<ecs::SpriteComponent>();
				if (spriteComponent != nullptr) {
					spriteComponent->Get
				}
			}
			else {
				nano::WriteToFile("none", true);
			}
		}
		
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