#pragma once

#include"EngineSystemBase.h"

#include<ecs\Entity.h>
#include<vector>

namespace nano { namespace engine {
	
	struct ScriptCommand {
		ecs::Entity* entity;
		std::string commandString;

		std::string arg1, arg2; // std::string being the most primitive type (I'm dumb this just makes it easy for converting)
		// This to avoid having inheritance and other ugly stuff
	};

	class ScriptingSystem : public EngineSystemBase<ScriptingSystem> {
	friend class EngineSystemBase<ScriptingSystem>;

	private:
		ScriptingSystem() { }

		std::vector<ScriptCommand> m_constantCommandsToExecute; 

	public:
		void start() override;
		void update() override;
		void shutdown() override;

		void parseScriptFiles();
		void processScriptCommands();

	};

} }