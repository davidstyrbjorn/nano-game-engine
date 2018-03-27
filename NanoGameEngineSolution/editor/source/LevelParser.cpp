#include"../include/LevelParser.h"

#include<ecs\Entity.h>
#include<graphics\Renderable.h>
#include<ecs\components\SpriteComponent.h>
#include<ecs\components\TriangleComponent.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\SoundComponent.h>

#include<asset\SoundAsset.h>
#include<asset\ImageAsset.h>

#include"../include/components/FourwayMoveComponentEditor.h"
#include"../include/systems/AssetSystem.h"

#include<fstream>

#include<StringHelp.h>
#include"../include/SerializerAPI.h"

namespace nano { namespace editor {

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

	bool LevelParser::GetParsedLevelFromFile(const char* a_levelFileName, ParsedLevel &a_level)
	{
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
		std::string assetName;

		// Sound Component only loads with a sound path so no info saving is needed

		FourwayMoveComponentEditor *fourwayMoveToAdd = nullptr;
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
			else if (line.substr(0, 8) == "cam_size") {
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
					z = std::stof(string.substr(string.find_first_of(',')+1, string.find_last_of(',')));
					w = std::stof(string.substr(string.find_last_of(',') + 1, string.length()));

					color = math::Vector4(x, y, z, w);
				}
				else if (line.substr(0, 16) == "image_asset_name") {
					assetName = line.substr(17, line.length());

					// Now add component!
					if (vertex_count == 3) {
						// Triangle 
						entityToAdd->AddComponent(new ecs::TriangleComponent(color));
					}
					else if (vertex_count == 4) {
						// Rectangle OR Sprite
						if (assetName == "none") {
							// Rectangle
							entityToAdd->AddComponent(new ecs::RectangleComponent(color));
						}
						else {
							// Sprite
							entityToAdd->AddComponent(new ecs::SpriteComponent());
							entityToAdd->GetComponent<ecs::SpriteComponent>()->LoadAsset(AssetSystem::getInstance()->getImageAssetByHndl(assetName));

						}
					}
				}
				// Sound Component
				// 1. Sound Path
				if (line.substr(0, 16) == "sound_asset_name") {
					std::string assetName = line.substr(17, line.length());
					if (assetName != "none") {
						entityToAdd->AddComponent(new ecs::SoundComponent());
						entityToAdd->GetComponent<ecs::SoundComponent>()->LoadAsset(AssetSystem::getInstance()->getSoundAssetByHndl(assetName));
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
					entityToAdd->AddComponent(new FourwayMoveComponentEditor(speed, keys));
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

	void LevelParser::ParseCurrentLevelToFile(const char* a_levelFileName, std::vector<ecs::Entity*> a_entities, math::Vector2 a_camPos, math::Vector2 a_camSize)
	{
		// Parse every config-thing i.e; background-color, camera-stuff etc		

		std::vector<ecs::Entity*> entitiesToSave = a_entities;

		nano::OpenOutputFile(a_levelFileName, OpenMode::TRUNCATE);

		// This is where we parse the entire fucking level into a text file with the correct format

		// Level Config
		nano::WriteToFile("[LEVEL_CONFIG]", true);
		std::string camPosString = "cam_pos " + to_string_with_precision<float>(a_camPos.x, 6) + ", " + to_string_with_precision<float>(a_camPos.y, 6);
		nano::WriteToFile(camPosString, true);
		std::string camSizeString = "cam_size " + std::to_string((int)(a_camSize.x+0.5f)) + ", " + std::to_string((int)(a_camSize.y+0.5f));
		nano::WriteToFile(camSizeString, true);
		std::string fpsString = "fps 60";
		nano::WriteToFile(fpsString.c_str(), true);

		nano::InsertBlankLine();

		// Level Entities and their components
		nano::WriteToFile("[LEVEL_ENTITIES]", true);
		for (ecs::Entity* entity : entitiesToSave) {
			nano::WriteToFile("[ENTITY]", true);

			// ID
			std::string entityIdString = "id " + entity->GetID();
			nano::WriteToFile(entityIdString.c_str(), true);

			// Transform
			nano::WriteToFile("transform", true);
			// dereferencing null pointer is a null-problem, we know every entity has a m_transform component on it
			ecs::Transform transform = *entity->m_transform;
			std::string posString = "pos " + transform.position.ToString();
			std::string sizeString = "size " + transform.size.ToString();
			std::string angleString = "angle " + to_string_with_precision<float>(transform.angle, 3);
			nano::WriteToFile(posString, true);
			nano::WriteToFile(sizeString, true);
			nano::WriteToFile(angleString, true);

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
					std::string imagePathString = "image_asset_name " + spriteComponent->getImageAsset()->getFileName();
					nano::WriteToFile(imagePathString, true);
				}
				else {
					nano::WriteToFile("image_asset_name none", true);
				}
			}
			else {
				nano::WriteToFile("none", true);
			}
			
			nano::WriteToFile("sound component", true);
			ecs::SoundComponent* soundComponent = entity->GetComponent<ecs::SoundComponent>();
			if (soundComponent != nullptr) {
				std::cout << "wait what" << std::endl;
				std::string soundPathString = "sound_asset_name " + std::string(soundComponent->getSoundAsset()->getFileName());
				nano::WriteToFile(soundPathString, true);
			}
			else {
				nano::WriteToFile("sound_asset_name none", true);
			}

			nano::WriteToFile("fourway move component", true);
			FourwayMoveComponentEditor *fwmComponent = entity->GetComponent<FourwayMoveComponentEditor>();
			if (fwmComponent != nullptr) {
				std::string upString = "up " + std::to_string(fwmComponent->GetKey("up"));
				std::string  rightString = "right " + std::to_string(fwmComponent->GetKey("right"));
				std::string downString = "down " + std::to_string(fwmComponent->GetKey("down"));
				std::string leftString = "left " + std::to_string(fwmComponent->GetKey("left"));
				// velocity should be reserved for physics terminology
				std::string velocityString = "speed " + to_string_with_precision<float>(fwmComponent->GetVelocity(), 3);

				nano::WriteToFile(upString, true);
				nano::WriteToFile(rightString, true);
				nano::WriteToFile(downString, true);
				nano::WriteToFile(leftString, true);
				nano::WriteToFile(velocityString, true);
			}
			else {
				nano::WriteToFile("none", true);
			}

			nano::InsertBlankLine();
		}

		nano::WriteToFile("[ENTITIES_END]");
		
		nano::CloseOutputFile();
	}

} }