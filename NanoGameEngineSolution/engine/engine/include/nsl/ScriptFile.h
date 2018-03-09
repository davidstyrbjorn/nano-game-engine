#pragma once

#include<string>
#include<vector>

#include"nsl_structs.h"

namespace nano {
	namespace ecs {
		class Entity;
} }

namespace nano { namespace engine {  

	class ScriptFile {
	public:
		// Constructor
		ScriptFile(const std::string& a_scriptString);
		// Destructor
		~ScriptFile();

		void parseScriptString();
		void executeScriptCommands();

	private:
		ecs::Entity* m_targetEntity;
		std::string m_fileHndl;
		std::vector<ScriptCommand> m_directCommands;

		const std::string m_scriptString;
	};

} }