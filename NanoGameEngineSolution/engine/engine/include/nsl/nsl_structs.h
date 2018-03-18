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
		std::string commandString;
		std::string arg;
	};

	struct ScriptLogicExpression {
		std::string logicString;
		std::string args;
		ScriptCommand command;
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