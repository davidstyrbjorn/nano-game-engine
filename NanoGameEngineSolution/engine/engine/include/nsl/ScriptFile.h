#pragma once

#include<string>
#include<vector>

#include"nsl_structs.h"

#include"../InputListener.h"

namespace nano {
	namespace engine {
		class InputSystem;
	}
	namespace ecs {
		class Entity;
	} 
}

namespace nano { namespace engine {  

	class ScriptFile : public InputListener {
	public:
		// Constructor
		ScriptFile(std::string a_hndl, std::vector<std::string> a_scriptStringVector);
		// Destructor
		~ScriptFile() {}
 
		void parseScriptString();
		void executeScriptCommands(float a_deltaTime);

	public:
		void onKeyPressed(int a_key) override;
		void onMousePressed(int a_key) override;
		void onMouseRelease(int a_key) override;
		void onKeyReleased(int a_key) override;

	private:
		bool doesLineContainParserToken(std::string a_line, std::string& a_foundParserToken);
		bool doesLineContainLogicExpression(std::string a_line, std::string& a_foundLogicExpression);
		bool doesLineContainCmdExpression(std::string a_line, std::string& a_foundCmdExpression);
		//bool doesLineContainVariable(std::string a_line, ScriptVariable& a_foundVariable);
		bool isLogicExpressionPassive(std::string a_expression);

		ScriptCommand getCommandFromString(std::string a_line);
		//void replaceVariableWithLiteralValues(std::string &a_subject);
		//const ScriptVariable getVariableFromName(std::string a_name);

		void commandGate(const ScriptCommand &a_command);

	private:
		ecs::Entity* m_targetEntity;
		std::string m_hndl;
		InputSystem *m_input;

		std::vector<ScriptCommand> m_directCommands;
		std::vector<ScriptLogicExpression> m_logicExpressions;
		std::vector<ScriptLogicExpression> m_passiveLogicExpressions;
		//std::vector<ScriptVariable> m_scriptVariables;

		std::vector<std::string> m_scriptStringVector; // Seperated line by line [0] = first line [1] = second line etc...
	};

} }