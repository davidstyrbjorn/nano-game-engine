#pragma once

#include"EditorSystem.h"
#include<string>

namespace nano { namespace editor {  

	class LevelParserSystem : EditorSystem {
	private:
		// Private constructor singleton pattern
		LevelParserSystem() { }
		static LevelParserSystem* _instance;

		// Datakkkkl
		std::string m_levelString;

	public:
		// Singleton connection
		LevelParserSystem* Instance();

		std::string GetLevelString();
		void ParseCurrentLevelToString();

		// Override
		void Start() override;
		void Update() override { }
		void Quit() override;
	};

} }