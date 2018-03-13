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
		void executeScriptCommands(float a_deltaTime);

	private:
		bool doesLineContainParserToken(std::string a_line, std::string& a_foundParserToken);
		bool doesLineContainLogicExpression(std::string a_line, std::string& a_foundLogicExpression);
		bool doesLineContainCmdExpression(std::string a_line, std::string& a_foundCmdExpression);
		bool doesLineContainVariable(std::string a_line, ScriptVariable& a_foundVariable);

		void replaceVariableWithLiteralValues(std::string &a_subject);
		const ScriptVariable getVariableFromName(std::string a_name);

		void commandGate(std::string a_command, std::string a_argument);

	private:
		ecs::Entity* m_targetEntity;
		std::string m_hndl;
		std::vector<ScriptCommand> m_directCommands;
		std::vector<ScriptLogicExpression> m_logicExpressions;
		std::vector<ScriptVariable> m_scriptVariables;

		std::vector<std::string> m_scriptStringVector; // Seperated line by line [0] = first line [1] = second line etc...
	};

} }