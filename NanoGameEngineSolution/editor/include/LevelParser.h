#pragma once

#include<string>
#include<vector>

#include<math\Vector2.h>

namespace nano {
	namespace ecs {
		class Entity;
} }

namespace nano { namespace editor {  

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

		bool GetParsedLevelFromFile(const char* a_levelFileName, ParsedLevel &a_level);
		std::string GetLevelStringFromFile(const char* a_levelFileName);

		void ParseCurrentLevelToFile(const char* a_levelFileName, std::vector<ecs::Entity*> a_entities, math::Vector2 a_camPos, math::Vector2 a_camSize);
	};
}
}