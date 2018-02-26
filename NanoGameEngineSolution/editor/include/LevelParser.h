#pragma once

#include<string>

namespace nano { namespace editor {  

	class LevelParser {
	private:		
		std::string m_levelString;

	public:
		LevelParser();

		std::string GetLevelStringFromFile(const char* a_filePath);
		void ParseCurrentLevelToFile(const char* a_filePath);
	};
} }