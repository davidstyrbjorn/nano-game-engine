#include "../include/nsl/ScriptFile.h"

#include<ecs\Entity.h>
#include<ecs\components\TransformComponent.h>

#include"../include/WorldSystem.h"
#include"../include/nsl/nsl_definitions.h"
#include"../include/nsl/CommandParser.h"

#include<assert.h>

#include<StringHelp.h>

namespace nano { namespace engine {  

	ScriptFile::ScriptFile(std::string a_hndl, std::vector<std::string> a_scriptStringVector)
	{
		m_hndl = a_hndl;
		m_scriptStringVector = a_scriptStringVector;
		parseScriptString();
	}

	ScriptFile::~ScriptFile()
	{

	}

	void ScriptFile::parseScriptString()
	{
		bool gotEntity = false;

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
									std::string argTemp = line.substr(line.find_last_of('('), line.length());
									if (doesLineContainVariable(argTemp, ScriptVariable())) {
										replaceVariableWithLiteralValues(argTemp);
									}
									logicExpr.command.arg = argTemp;
								}
								else {
									std::cout << "Was not able to parse line: " << line << " within file: " << m_hndl << std::endl;
								}
							
								m_logicExpressions.push_back(logicExpr);
							}
						}
					}
					else if(doesLineContainCmdExpression(line, command)){
						// Direct command!
						remove_space<std::string>(line);
						ScriptCommand directCmd;
						directCmd.commandString = command;
						std::string argTemp = line.substr(line.find('('), line.length());
						if (doesLineContainVariable(argTemp, ScriptVariable())) {
							replaceVariableWithLiteralValues(argTemp);
						}
						directCmd.arg = argTemp;
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
		for (ScriptCommand cmd : m_directCommands) {
			commandGate(cmd.commandString, cmd.arg);
		}
		for (ScriptLogicExpression logicExpr : m_logicExpressions) {
			if (logicExpr.logicString == "keyDown") {
				if (isKeyDownExpressionTrue(logicExpr.args)) {
					commandGate(logicExpr.command.commandString, logicExpr.command.arg);
				}
			}
		}
	}

	void ScriptFile::commandGate(std::string a_command, std::string a_argument)
	{
		if (a_command == "move") {
			moveCommand(m_targetEntity, a_argument);
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

	void ScriptFile::replaceVariableWithLiteralValues(std::string & a_subject)
	{
		bool isVariable[32];
		std::vector<std::string> variableSubStrings;
		int startIndex, endIndex;

		// This just fucking goes in and splits the shit into substrings
		// @TODO: Clean this mess up please
		int i = 0; for (char c : a_subject) {
			if (c == '(') {
				if (a_subject[i + 1] != '$') {
					startIndex = i;
				}
			}
			if (c == '$') {
				startIndex = i-1;
			}
			if (c == ',' || c == ')') {
				endIndex = i;
				variableSubStrings.push_back(a_subject.substr(startIndex, endIndex - startIndex));
				if (c == ',') {
					if (a_subject[i + 1] != '$') {
						startIndex = i;
					}
				}
			}
			i++;
		}

		// Go through each fucking substring and replace all the $ literal with its variable value
		std::vector<std::string> correctValueSubStrings;

		for (auto subVariableString : variableSubStrings) {
			int j = 0; for (char c : subVariableString) {
				if (c == ',' || c == '(') {
					if (subVariableString[j + 1] != '$') {
						correctValueSubStrings.push_back(subVariableString);
					}
				}
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
