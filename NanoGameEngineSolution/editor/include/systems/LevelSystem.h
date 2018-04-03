#pragma once

#include"EditorSystem.h"
#include<string>

namespace nano { namespace editor {  

	class LevelSystem : public EditorSystem<LevelSystem> {
		friend class EditorSystem<LevelSystem>;

	public:
		void Start() override;
		void Update() override {}
		void Quit() override {}

		void newLevel();
		bool loadLevel(std::string a_name);
		void saveLevel(std::string a_name);
	};

} }