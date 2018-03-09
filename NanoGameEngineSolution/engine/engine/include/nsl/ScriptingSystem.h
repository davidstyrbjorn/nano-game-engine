#pragma once

#include"../EngineSystemBase.h"

#include<vector>

#include"ScriptFile.h"

namespace nano { namespace engine {

	class ScriptingSystem : public EngineSystemBase<ScriptingSystem> {
	friend class EngineSystemBase<ScriptingSystem>;

	private:
		ScriptingSystem() { }

		std::vector<ScriptFile> m_scriptFiles;
		bool m_keysDown[1028];

		void readFilesFromDir(std::string a_dir, std::vector<std::string>& a_list);

	public:
		void start() override;
		void update() override;
		void shutdown() override;

		void parseScriptFiles();
		void processScriptCommands();

	};

} }