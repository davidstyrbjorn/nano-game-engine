#include"../include/LevelParser.h"

#include<ecs\Entity.h>
#include<graphics\Renderable.h>
#include<ecs\components\SpriteComponent.h>
#include<ecs\components\TriangleComponent.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\SoundComponent.h>

#include"../include/components/FourwayMoveComponentEngine.h"
#include"../include/AssetSystem.h"

#include<fstream>

#include<StringHelp.h>
#include"../include/SerializerAPI.h"

#include<asset\ImageAsset.h>
#include<asset\SoundAsset.h>

namespace nano { namespace engine {

	std::vector<std::string> LevelParser::GetSegmentedString(std::string a_stringToSplit)
	{
		std::vector<std::string> segmentedString;
		std::stringstream ss(a_stringToSplit);
		std::string segment;

		while (std::getline(ss, segment, '\n')) {
			segmentedString.push_back(segment);
		}

		return segmentedString;
	}

	LevelParser::LevelParser()
	{
	}

	ecs::Entity * LevelParser::getParsedEntityFromFile(const char * a_fileName)
	{
		// Hehe
		ecs::Entity* baby = new ecs::Entity("unnamed");
		if (!nano::OpenInputFile(a_fileName)) {
			return nullptr;
		}

		// Get the file string
		std::string fileContent;
		GetAllFileContent(fileContent);
		std::vector<std::string> segmentedString = GetSegmentedString(fileContent);

		static math::Vector4 color;
		static int vertex_count, up, right, down, left;

		for (std::string line : segmentedString) {
			if (line.substr(0, 2) == "id") {
				std::string id = line.substr(3, line.length() - 3);
				baby->SetID(id);
			}
			// Position
			else if (line.substr(0, 3) == "pos") {
				int splitIndex = line.find(',');
				float x = std::stof(line.substr(4, splitIndex));
				float y = std::stof(line.substr(splitIndex + 1, line.length()));
				baby->m_transform->position = math::Vector2(x, y);
			}
			// Size
			else if (line.substr(0, 4) == "size") {
				int splitIndex = line.find(',');
				float x = std::stof(line.substr(5, splitIndex));
				float y = std::stof(line.substr(splitIndex + 1, line.length()));
				baby->m_transform->size = math::Vector2(x, y);
			}
			// Angle
			else if (line.substr(0, 5) == "angle") {
				float angle = std::stoi(line.substr(6, line.length()));
				baby->m_transform->angle = angle;
			}
			// Renderable 
			// 1. vertex_count
			else if (line.substr(0, 12) == "vertex_count") {
				vertex_count = std::stoi(line.substr(13, line.length()));
			}
			else if (line.substr(0, 5) == "color") {
				float x, y, z, w;
				int splitIndex1, splitIndex2, splitIndex3;
				std::string string = line.substr(6, line.length());
				x = std::stof(string.substr(0, line.find_first_of(',')));
				string = line.substr(line.find_first_of(',') + 1, line.length());

				// String should now be y, z, w
				y = std::stof(string.substr(0, string.find_first_of(',')));
				z = std::stof(string.substr(string.find_first_of(',') + 1, string.find_last_of(',')));
				w = std::stof(string.substr(string.find_last_of(',') + 1, string.length()));

				color = math::Vector4(x, y, z, w);
			}
			else if (line.substr(0, 16) == "image_asset_name") {
				std::string assetName = line.substr(17, line.length());

				// Now add component!
				if (vertex_count == 3) {
					// Triangle 
					baby->AddComponent(new ecs::TriangleComponent(color));
				}
				else if (vertex_count == 4) {
					// Rectangle OR Sprite
					if (assetName == "none") {
						// Rectangle
						baby->AddComponent(new ecs::RectangleComponent(color));
					}
					else {
						// Sprite
						baby->AddComponent(new ecs::SpriteComponent());
						baby->GetComponent<ecs::SpriteComponent>()->LoadAsset(AssetSystem::getInstance()->getImageAssetByHndl(assetName));
					}
				}
			}
			// Sound Component
			// 1. Sound Path
			if (line.substr(0, 16) == "sound_asset_name") {
				std::string assetName = line.substr(17, line.length());
				baby->AddComponent(new ecs::SoundComponent());
				if (assetName != "none") {
					baby->GetComponent<ecs::SoundComponent>()->LoadAsset(AssetSystem::getInstance()->getSoundAssetByHndl(assetName));
				}
			}
			// FourwayMoveComponentEditor 
			// 1. up
			if (line.substr(0, 2) == "up") {
				up = std::stoi(line.substr(3, line.length()));
			}
			// 2. right
			else if (line.substr(0, 5) == "right") {
				right = std::stoi(line.substr(6, line.length()));
			}
			// 3. down
			else if (line.substr(0, 4) == "down") {
				down = std::stoi(line.substr(5, line.length()));
			}
			// 4. left
			else if (line.substr(0, 4) == "left") {
				left = std::stoi(line.substr(5, line.length()));
			}
			// 5. speed (and done now add component)
			else if (line.substr(0, 5) == "speed") {
				float speed = std::stof(line.substr(6, line.length()));
				int keys[4] = { up, right, down, left };
				baby->AddComponent(new FourwayMoveComponentEngine(speed, keys));
			}
		}

		nano::CloseInputFile();
		return baby;
	}

	bool LevelParser::GetParsedLevelFromFile(const char* a_levelFileName, ParsedLevel &a_level)
	{
		static AssetSystem *assetSystem = AssetSystem::getInstance();

		std::string levelString = GetLevelStringFromFile(a_levelFileName);
		if (levelString == "NULL") {
			return false;
		}

		// [0] will be [LEVEL_CONFIG] if not the text file is not a level
		std::vector<std::string> segmentedLevelString = GetSegmentedString(levelString);
		std::vector<ecs::Entity*> entities;

		if (segmentedLevelString[0] != "[LEVEL_CONFIG]") {
			return false;
		}

		ecs::Entity* entityToAdd = nullptr;
		// Current Renderable info
		int vertex_count;
		math::Vector4 color;
		std::string path;

		// Sound Component only loads with a sound path so no info saving is needed

		//FourwayMoveComponentEditor *fourwayMoveToAdd = nullptr;
		// Current fourway move info
		int up, right, down, left;
		float speed;

		for (std::string line : segmentedLevelString)
		{
			if (line.substr(0, 7) == "cam_pos") {
				int splitIndex = line.find(',');
				a_level.camPos.x = std::stof(line.substr(8, splitIndex));
				a_level.camPos.y = std::stof(line.substr(splitIndex + 1, line.length()));
			}
			if (line.substr(0, 8) == "cam_size") {
				int splitIndex = line.find(',');
				a_level.camSize.x = std::stof(line.substr(9, splitIndex));
				a_level.camSize.y = std::stof(line.substr(splitIndex + 1, line.length()));
			}

			if (line == "[ENTITY]") {
				if (entityToAdd == nullptr) {
					// This is the first so just create a new entity
					entityToAdd = new ecs::Entity("untitled");
				}
				else {
					// We're now on a new entity so push back the old and reset (call new on EntityToAdd)
					entities.push_back(entityToAdd);
					entityToAdd = new ecs::Entity("untitled");
				}
			}
			else if (line == "[ENTITIES_END]") {
				if (entityToAdd != nullptr) {
					entities.push_back(entityToAdd);
					entityToAdd = nullptr;
				}
			}

			if (entityToAdd != nullptr) {
				// Entity ID
				if (line.substr(0, 2) == "id") {
					entityToAdd->SetID(line.substr(3, line.length()));
				}
				// Transform
				// Position
				if (line.substr(0, 3) == "pos") {
					int splitIndex = line.find(',');
					float x = std::stof(line.substr(4, splitIndex));
					float y = std::stof(line.substr(splitIndex + 1, line.length()));
					entityToAdd->m_transform->position = math::Vector2(x, y);
				}
				// Size
				else if (line.substr(0, 4) == "size") {
					int splitIndex = line.find(',');
					float x = std::stof(line.substr(5, splitIndex));
					float y = std::stof(line.substr(splitIndex + 1, line.length()));
					entityToAdd->m_transform->size = math::Vector2(x, y);
				}
				// Angle
				else if (line.substr(0, 5) == "angle") {
					float angle = std::stoi(line.substr(6, line.length()));
					entityToAdd->m_transform->angle = angle;
				}
				// Renderable 
				// 1. vertex_count
				else if (line.substr(0, 12) == "vertex_count") {
					vertex_count = std::stoi(line.substr(13, line.length()));
				}
				else if (line.substr(0, 5) == "color") {
					float x, y, z, w;
					int splitIndex1, splitIndex2, splitIndex3;
					std::string string = line.substr(6, line.length());
					x = std::stof(string.substr(0, line.find_first_of(',')));
					string = line.substr(line.find_first_of(',') + 1, line.length());

					// String should now be y, z, w
					y = std::stof(string.substr(0, string.find_first_of(',')));
					z = std::stof(string.substr(string.find_first_of(',') + 1, string.find_last_of(',')));
					w = std::stof(string.substr(string.find_last_of(',') + 1, string.length()));

					color = math::Vector4(x, y, z, w);
				}
				// Now add component!

				else if (line.substr(0, 16) == "image_asset_name") {
					path = line.substr(17, line.length());
					if (vertex_count == 3) {
						// Triangle 
						entityToAdd->AddComponent(new ecs::TriangleComponent(color));
					}
					else if (vertex_count == 4) {
						// Rectangle OR Sprite
						if (path == "none") {
							// Rectangle
							entityToAdd->AddComponent(new ecs::RectangleComponent(color));
						}
						else {
							// Sprite
							// Get asset using asset name here
							entityToAdd->AddComponent(new ecs::SpriteComponent());
							entityToAdd->GetComponent<ecs::SpriteComponent>()->LoadAsset(assetSystem->getImageAssetByHndl(path));
						}
					}
				}
				// Sound Component
				// 1. Sound Path
				if (line.substr(0, 16) == "sound_asset_name") {
					std::string path = line.substr(17, line.length());
					// Get sound asset using asset name here
					entityToAdd->AddComponent(new ecs::SoundComponent());
					if (path != "none") {
						entityToAdd->GetComponent<ecs::SoundComponent>()->LoadAsset(assetSystem->getSoundAssetByHndl(path));
					}
				}
				// FourwayMoveComponentEditor 
				// 1. up
				if (line.substr(0, 2) == "up") {
					up = std::stoi(line.substr(3, line.length()));
				}
				// 2. right
				else if (line.substr(0, 5) == "right") {
					right = std::stoi(line.substr(6, line.length()));
				}
				// 3. down
				else if (line.substr(0, 4) == "down") {
					down = std::stoi(line.substr(5, line.length()));
				}
				// 4. left
				else if (line.substr(0, 4) == "left") {
					left = std::stoi(line.substr(5, line.length()));
				}
				// 5. speed (and done now add component)
				else if (line.substr(0, 5) == "speed") {
					speed = std::stof(line.substr(6, line.length()));
					int keys[4] = { up, right, down, left };
					entityToAdd->AddComponent(new FourwayMoveComponentEngine(speed, keys));
				}
			}
		}

		a_level.entities = entities;

		return true;
	}

	std::string LevelParser::GetLevelStringFromFile(const char* a_levelFileName)
	{
		if (!OpenInputFile(std::string(std::string(a_levelFileName)).c_str())) {
			return "NULL";
		}
		std::string levelString;
		GetAllFileContent(levelString);
		CloseInputFile();
		return levelString;
	}
} }