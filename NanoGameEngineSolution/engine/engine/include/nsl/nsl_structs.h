#pragma once

#include<string>
#include<vector>

namespace nano {
	namespace ecs {
		class Entity;
	}
}

namespace nano { namespace engine {  

	struct ScriptCommand {
		ScriptCommand(std::string a_commandString, std::string a_arg) : commandString(a_commandString), arg(a_arg) { } 
		ScriptCommand(std::string a_commandString, int a_integerArg) : commandString(a_commandString) { }
		ScriptCommand() {}

		std::string commandString;
		std::string arg;
		int integerArg[10];
		float floatArg[10];
	};

	struct ScriptLogicExpression {
		ScriptCommand command;
		std::string logicString;
		std::string args;
	};

	struct ScriptVariable {
		std::string name;
		std::string value;

		ScriptVariable() { }
		ScriptVariable(std::string a_name, std::string a_value) : name(a_name), value(a_value) { }
	};

	static void addBuiltInVariables(std::vector<ScriptVariable>& a_varList) {
		a_varList.push_back(ScriptVariable("KEY_A", "65"));
		a_varList.push_back(ScriptVariable("KEY_D", "68"));
		a_varList.push_back(ScriptVariable("KEY_W", "87"));
		a_varList.push_back(ScriptVariable("KEY_S", "83"));
	}
   
} }