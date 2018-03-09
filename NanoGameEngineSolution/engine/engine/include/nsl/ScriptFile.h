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
		ScriptFile(std::string a_hndl, std::vector<std::string> a_scriptStringVector);
		// Destructor
		~ScriptFile();

		void parseScriptString();
		void executeScriptCommands();

	private:
		bool doesLineContainCmdExpression(std::string a_line, std::string& a_foundCmdExpression);

	private:
		ecs::Entity* m_targetEntity;
		std::string m_hndl;
		std::vector<ScriptCommand> m_directCommands;

		std::vector<std::string> m_scriptStringVector; // Seperated line by line [0] = first line [1] = second line etc...
	};

} }