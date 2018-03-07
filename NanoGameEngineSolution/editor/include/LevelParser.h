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
		int fps;
	};

	class LevelParser {
	private:		
		std::string m_levelString;

		std::vector<std::string> GetSegmentedString(std::string a_stringToSplit);

	public:
		LevelParser();

		template<class T>
		inline bool GetParsedLevelFromFile(const char* a_levelFileName, ParsedLevel &a_level);
		std::string GetLevelStringFromFile(const char* a_levelFileName);

		void ParseCurrentLevelToFile(const char* a_levelFileName, std::vector<ecs::Entity*> a_entities, math::Vector2 a_camPos);
	};

	template<class T>
	inline bool LevelParser::GetParsedLevelFromFile(const char * a_levelFileName, ParsedLevel & a_level)
	{
		return false;
	}
	// @TODO: Implement in .cpp file please
}
}