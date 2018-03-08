#include"../include/LevelParser.h"

#include<ecs\Entity.h>
#include<graphics\Renderable.h>
#include<ecs\components\SpriteComponent.h>
#include<ecs\components\TriangleComponent.h>
#include<ecs\components\RectangleComponent.h>
#include<ecs\components\TransformComponent.h>
#include<ecs\components\SoundComponent.h>

#include<fstream>

#include<StringHelp.h>
#include"../include/SerializerAPI.h"

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
				else if (line.substr(0, 10) == "image_path") {
					path = line.substr(11, line.length());

					// Now add component!
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
							entityToAdd->AddComponent(new ecs::SpriteComponent(path.c_str()));
						}
					}
				}
				// Sound Component
				// 1. Sound Path
				if (line.substr(0, 10) == "sound_path") {
					std::string path = line.substr(11, line.length());
					entityToAdd->AddComponent(new ecs::SoundComponent(path.c_str()));
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
					//entityToAdd->AddComponent(new FourwayMoveComponentEditor(speed, keys));
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