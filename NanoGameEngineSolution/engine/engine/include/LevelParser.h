#pragma once

#include<string>
#include<vector>

#include<math\Vector2.h>

namespace nano {
	namespace ecs {
		class Entity;
	}
}

namespace nano { namespace engine {

	struct ParsedLevel {
		std::vector<ecs::Entity*> entities;
		math::Vector2 camPos;
		math::Vector2 camSize;
		int fps;
	};

	class LevelParser {
	private:
		std::string m_levelString;

		std::vector<std::string> GetSegmentedString(std::string a_stringToSplit);

	public:
		LevelParser();

		ecs::Entity* getParsedEntityFromFile(const char* a_name);
		bool GetParsedLevelFromFile(const char* a_levelFileName, ParsedLevel &a_level);
		std::string GetLevelStringFromFile(const char* a_levelFileName);
	};

} }