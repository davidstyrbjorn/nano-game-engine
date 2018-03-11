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
						if (parserToken == "if") {
							std::string logicExpression;
							if (doesLineContainLogicExpression(line, logicExpression)) {
								ScriptLogicExpression logicExpr;
								// Logic expression string
								logicExpr.logicString = logicExpression; // keyDown etc

								// Set the arguments from the example keyDown(args)
								int startArgIndex = line.find("(");
								int endArgIndex = line.find(")")+1;
								std::string argTemp = line.substr(startArgIndex, endArgIndex - startArgIndex);
								// Check if argument is a registered variable
								ScriptVariable variable;
								if (doesLineContainVariable(argTemp, variable)) {
									// Replace argTemp with variable.value?

								}
								logicExpr.args = line.substr(startArgIndex, endArgIndex-startArgIndex);

								// Command
								if (doesLineContainCmdExpression(line, logicExpr.command.commandString)) {
									logicExpr.command.arg = line.substr(line.find_last_of('('), line.length());
								}
								else {
									std::cout << "Was not able to parse line: " << line << " within file: " << m_hndl << std::endl;
								}
							
								m_logicExpressions.push_back(logicExpr);
							}
						}
						else if (parserToken == "var") {
							//std::cout << "found var parser token! " << line << std::endl;
							// Get variable name
							ScriptVariable sv;

							remove_space<std::string>(line);

							int end = line.find(':');
							int start = line.find('$')+1;

							sv.name = line.substr(start, end - start);
							sv.value = line.substr(end+1);

							m_scriptVariables.push_back(sv);
						}
					}
					else if(doesLineContainCmdExpression(line, command)){
						// Direct command!
						ScriptCommand directCmd;
						directCmd.commandString = command;
						directCmd.arg = line.substr(line.find('('), line.length());
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
		//for (ScriptCommand cmd : m_directCommands) {
		//	if (cmd.commandString == "move") {
		//		// Process move command please
		//		moveCommand(m_targetEntity, cmd.arg);
		//	}
		//}
		//for (ScriptLogicExpression logicExpr : m_logicExpressions) {
		//	if (logicExpr.logicString == "keyDown") {
		//		if (isKeyDownExpressionTrue(logicExpr.args)) {
		//			if (logicExpr.command.commandString == "move") {
		//				moveCommand(m_targetEntity, logicExpr.command.arg);
		//			}
		//		}
		//	}
		//}
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
