#include "../include/nsl/ScriptFile.h"

#include<ecs\Entity.h>
#include<ecs\components\TransformComponent.h>

#include"../include/WorldSystem.h"
#include"../include/InputSystem.h"
#include"../include/nsl/nsl_definitions.h"
#include"../include/nsl/CommandParser.h"

#include<assert.h>

#include<StringHelp.h>

namespace nano { namespace engine {  

	ScriptFile::ScriptFile(std::string a_hndl, std::vector<std::string> a_scriptStringVector)
	{
		m_hndl = a_hndl;
		m_scriptStringVector = a_scriptStringVector;
		m_input = InputSystem::getInstance();
	}

	void ScriptFile::parseScriptString()
	{
		bool gotEntity = false;
		addBuiltInVariables(m_scriptVariables);

		for (std::string line : m_scriptStringVector)
		{
			if (line != "") {
				// using_entity
				if (line.substr(0, 12) == "using_entity" && !gotEntity) {
					std::string id = line.substr(line.find_first_of('$') + 1, line.length());
					m_targetEntity = WorldSystem::getInstance()->getEntityByID(id);
					gotEntity = true;
				}
				else if (gotEntity) {
					// Parse in this order, check for parser tokens else assume the line is a direct command
					std::string parserToken;
					std::string command;

					if (line[0] == '#') {
						// Comment
					}
					else if (doesLineContainParserToken(line, parserToken)) {
						if (parserToken == "var") {
							//std::cout << "found var parser token! " << line << std::endl;
							// Get variable name
							ScriptVariable sv;

							remove_space<std::string>(line);

							int end = line.find(':');
							int start = line.find('$') + 1;

							sv.name = line.substr(start, end - start);
							sv.value = line.substr(end + 1);

							//std::cout << "Registered variable " << sv.name << " with value " << sv.value << std::endl;
							m_scriptVariables.push_back(sv);
						}
						else if (parserToken == "if") {
							std::string logicExpression;
							if (doesLineContainLogicExpression(line, logicExpression)) {
								// Removing any spaces from the line 
								remove_space<std::string>(line);

								ScriptLogicExpression logicExpr;
								// Logic expression string
								logicExpr.logicString = logicExpression; // keyDown etc

								// Set the arguments from the example keyDown(args)
								int startArgIndex = line.find("(");
								int endArgIndex = line.find(")")+1;
								std::string argTemp = line.substr(startArgIndex, endArgIndex - startArgIndex);
								if (doesLineContainVariable(argTemp, ScriptVariable())) {
									replaceVariableWithLiteralValues(argTemp);
								}
								logicExpr.args = argTemp;

								// Command
								if (doesLineContainCmdExpression(line, logicExpr.command.commandString)) {
									// Assumed format is command(arg)
									std::string temp = line.substr(line.find(':')+1, line.length());
									ScriptCommand cmd = getCommandFromString(temp);
									logicExpr.command = cmd;

									//std::string argTemp = line.substr(line.find_last_of('('), line.length());
									//if (doesLineContainVariable(argTemp, ScriptVariable())) {
									//	replaceVariableWithLiteralValues(argTemp);
									//}
									//logicExpr.command.arg = argTemp;
								}
								else {
									std::cout << "Was not able to parse line: " << line << " within file: " << m_hndl << std::endl;
								}
							
								if (isLogicExpressionPassive(logicExpression)) {
									m_passiveLogicExpressions.push_back(logicExpr);
								}
								else {
									m_logicExpressions.push_back(logicExpr);
								}
							}
						}
					}
					else if(doesLineContainCmdExpression(line, command)){
						// Direct command!
						remove_space<std::string>(line);
						ScriptCommand directCmd = getCommandFromString(line);
						m_directCommands.push_back(directCmd);	
					}
					else {
						std::cout << "Was not able to parse line: " << line << " within file: " << m_hndl << std::endl;
					}
				}
			}
		}
	}

	void ScriptFile::executeScriptCommands(float a_deltaTime)
	{
		// Go through direct commands
		for (ScriptCommand cmd : m_directCommands) {
			commandGate(cmd);
		}
		// Go through the normal logic expressions
		for (ScriptLogicExpression logicExpr : m_logicExpressions) {
			if (logicExpr.logicString == "keyDown") {
				if (isKeyDownExpressionTrue(logicExpr.args)) {
					commandGate(logicExpr.command);
				}
			}
		}
	}

	void ScriptFile::onKeyPressed(int a_key)
	{
		for (ScriptLogicExpression passiveExpression : m_passiveLogicExpressions) {
			if (passiveExpression.logicString == "keyPressed") {
				if (getKeyCodeLiteralFromArg(passiveExpression.args) == a_key) {
					commandGate(passiveExpression.command);
				}
			}
		}
	}

	void ScriptFile::onMousePressed(int a_key)
	{
		for (ScriptLogicExpression passiveExpression : m_passiveLogicExpressions) {
			if (passiveExpression.logicString == "mousePressed") {
				if (getKeyCodeLiteralFromArg(passiveExpression.args) == a_key) {
					commandGate(passiveExpression.command);
				}
			}
		}
	}

	void ScriptFile::onMouseRelease(int a_key)
	{
		for (ScriptLogicExpression passiveExpression : m_passiveLogicExpressions) {
			if (passiveExpression.logicString == "mouseReleased") {
				if (getKeyCodeLiteralFromArg(passiveExpression.args) == a_key) {
					commandGate(passiveExpression.command);
				}
			}
		}
	}

	void ScriptFile::onKeyReleased(int a_key)
	{
		for (ScriptLogicExpression passiveExpression : m_passiveLogicExpressions) {
			if (passiveExpression.logicString == "keyReleased") {
				if (getKeyCodeLiteralFromArg(passiveExpression.args) == a_key) {
					commandGate(passiveExpression.command);
				}
			}
		}
	}

	void ScriptFile::commandGate(const ScriptCommand &a_command)
	{
		if (a_command.commandString == "move") {
			moveCommand(m_targetEntity, a_command.integerArg[0], a_command.integerArg[1], a_command.floatArg[0]);
		}
		else if (a_command.commandString == "setPosition") {
			setPositionCommand(m_targetEntity, a_command.arg);
		}
		else if (a_command.commandString == "setSize") {
			setSizeCommand(m_targetEntity, a_command.arg);
		}
		else if (a_command.commandString == "create") {
			createCommand(a_command.arg);
		}
		else if (a_command.commandString == "destroy") {
			destroyCommand(a_command.arg);
		}
	}

	bool ScriptFile::doesLineContainCmdExpression(std::string a_line, std::string & a_foundCmdExpression)
	{
		// move, destroy, create etc
		for (std::string cmdExpression : cmdExpressions) {
			if (a_line.find(cmdExpression) != std::string::npos) {
				a_foundCmdExpression = cmdExpression;
				return true;
			}
		}
		return false;
	}

	bool ScriptFile::doesLineContainVariable(std::string a_line, ScriptVariable& a_foundVariable)
	{
		// $speed, $keyLeft etc
		for (ScriptVariable variable : m_scriptVariables) {
			if (a_line.find(variable.name) != std::string::npos) {
				a_foundVariable = variable;
				return true;
			}
		}
		return false;
	}

	bool ScriptFile::isLogicExpressionPassive(std::string a_expression)
	{
		for (std::string passiveExpression : passiveLogicExpressions) {
			if (a_expression == passiveExpression)
				return true;
		}
		return false;
	}

	ScriptCommand ScriptFile::getCommandFromString(std::string a_line)
	{
		// Assumed format 
		// command(arg)
		// arg can be whatever but if it's supposed to be interperted as an integer set command.argInteger 
		// Else just set command.arg
		ScriptCommand command;

		command.commandString = a_line.substr(0, a_line.find('('));

		std::string tempArg = a_line.substr(a_line.find('('), a_line.length());
		if (doesLineContainVariable(a_line, ScriptVariable())) {
			replaceVariableWithLiteralValues(tempArg);
		}
		command.arg = tempArg;

		// Here we replace arg(string) with numbers-ish if the command has those parameters
		if (command.commandString == "move") { // move(int, int, float)
			command.integerArg[0] = std::stoi(tempArg.substr(1, tempArg.find_first_of(identifierSplit)));
			command.integerArg[1] = std::stoi(tempArg.substr(tempArg.find_first_of(identifierSplit) + 1, tempArg.find_last_of(identifierSplit)));
			command.floatArg[0] = std::stof(tempArg.substr(tempArg.find_last_of(identifierSplit) + 1, tempArg.length() - 1));
		}
		if (command.commandString == "setPosition" || command.commandString == "setSize") { // setPos&SetSize(a, b)
			int start = tempArg.find(',');
			int end = tempArg.find(')');
			command.floatArg[0] = std::stof(tempArg.substr(1, start));
			command.floatArg[1] = std::stof(tempArg.substr(start + 1, end - (start + 1)));
		}

		return command; // Return copy of command created
	}

	void ScriptFile::replaceVariableWithLiteralValues(std::string & a_subject)
	{
		std::vector<std::string> variableSubStrings;

		// @TODO: Clean this mess up, looks dirty
		int startIndex, endIndex;
		int i = 0; for (char c : a_subject) {
			if (c == '(') {
				startIndex = i;
			}
			if (c == ',' || c == ')') {
				endIndex = i;
				variableSubStrings.push_back(a_subject.substr(startIndex, endIndex - startIndex));
				startIndex = i;
			}
			i++;
		}
		// Go through each fucking substring and replace all the $ literal with its variable value
		std::vector<std::string> correctValueSubStrings;
		for (auto subVariableString : variableSubStrings) {
			int j = 0; for (char c : subVariableString) {
				// Make sure we add non-variable literal values as well to the correct return string
				if (c == ',' || c == '(') {
					if (subVariableString[j + 1] != '$') {
						correctValueSubStrings.push_back(subVariableString);
					}
				}
				// Found variable now replace it with its value and insert into correct return string
				if (c == '$') {
					ScriptVariable var = getVariableFromName(subVariableString.substr(j + 1));
					std::string copy = subVariableString;
					copy.erase(j);
					copy.insert(j, var.value);
					correctValueSubStrings.push_back(copy);
				}
				j++;
			}
		}

		a_subject = "";
		for (int i = 0; i < correctValueSubStrings.size(); i++) {
			a_subject += correctValueSubStrings.at(i);
			if (i == correctValueSubStrings.size()-1)
				a_subject += ")";
		}
	}

	const ScriptVariable ScriptFile::getVariableFromName(std::string a_name)
	{
		for (ScriptVariable var : m_scriptVariables) {
			if (var.name == a_name)
				return var;
		}
		std::cout << "Variable not found" << std::endl;
		return ScriptVariable();
	}

	bool ScriptFile::doesLineContainParserToken(std::string a_line, std::string & a_foundParserToken)
	{
		// if, then, var
		for (std::string parserToken : parserTokens) {
			if (a_line.find(parserToken) != std::string::npos) {
				a_foundParserToken = parserToken;
				return true;
			}
		}
		return false;
	}

	bool ScriptFile::doesLineContainLogicExpression(std::string a_line, std::string & a_foundLogicExpression)
	{
		// keyDown etc
		for (std::string logicExpression : logicExpressions) {
			if (a_line.find(logicExpression) != std::string::npos) {
				a_foundLogicExpression = logicExpression;
				return true;
			}
		}
		return false;
	}

} }
