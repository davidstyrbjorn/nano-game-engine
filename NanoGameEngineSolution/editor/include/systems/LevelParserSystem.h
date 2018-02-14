#pragma once

#include"EditorSystem.h"
#include<string>

namespace nano { namespace editor {  

	class LevelParserSystem : EditorSystem {
	private:
		// Private constructor singleton pattern
		LevelParserSystem() { }
		static LevelParserSystem* _instance;

		
		std::string m_levelString;

	public:
		// Singleton connection
		static LevelParserSystem* Instance();

		std::string GetLevelStringFromFile(const char* a_filePath);
		void ParseCurrentLevelToFile(const char* a_filePath);
					    
		// Override
		void Start() override;
		void Update() override { }
		void Quit() override;
	};

} }