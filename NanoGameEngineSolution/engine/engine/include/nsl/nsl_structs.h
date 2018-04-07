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
   
} }