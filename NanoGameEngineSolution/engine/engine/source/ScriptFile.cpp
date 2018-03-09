#include "../include/nsl/ScriptFile.h"

#include<ecs\Entity.h>
#include<ecs\components\TransformComponent.h>

#include"../include/WorldSystem.h"
#include"../include/nsl/nsl_definitions.h"

#include"../include/nsl/CommandParser.h"

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
					// Now we can parse commands 
					if (line.substr(0, 2) == "if") {
						// We don't handle this atm
						std::string logicExpression;
						if (doesLineContainLogicExpression(line, logicExpression)) {
							ScriptLogicExpression logicExpr;

							// Logic expression string
							logicExpr.logicString = logicExpression;
							int firstParanthesisIndex = line.find_first_of('(');
							int firstClosingParanthesisIndex = line.find_first_of(')');
							logicExpr.args = line.substr(firstParanthesisIndex, firstClosingParanthesisIndex);
							// Command
							doesLineContainCmdExpression(line, logicExpr.command.commandString);
							logicExpr.command.arg = line.substr(line.find_last_of('('), line.length());

							m_logicExpressions.push_back(logicExpr);
						}
					}
					else {
						// Direct command!
						std::string command;
						if (doesLineContainCmdExpression(line, command)) {
							ScriptCommand directCmd;
							directCmd.commandString = command;
							directCmd.arg = line.substr(line.find('('), line.length());
							m_directCommands.push_back(directCmd);
						}
						else {
							std::cout << "error parsing line from script file with handel " + m_hndl << std::endl;
							std::cout << "(line: " << line << ")" << std::endl;
						}
					}
				}
			}
		}
	}

	void ScriptFile::executeScriptCommands()
	{
		for (ScriptCommand cmd : m_directCommands) {
			if (cmd.commandString == "move") {
				// Process move command please
				moveCommand(m_targetEntity, cmd.arg);
			}
		}
		for (ScriptLogicExpression logicExpr : m_logicExpressions) {
			if (logicExpr.logicString == "keyDown") {
				if (isKeyDownExpressionTrue(logicExpr.args)) {
					if (logicExpr.command.commandString == "move") {
						moveCommand(m_targetEntity, logicExpr.command.arg);
					}
				}
			}
		}
	}

	bool ScriptFile::doesLineContainCmdExpression(std::string a_line, std::string & a_foundCmdExpression)
	{
		// in-arg = line from script file, found expression reference 
		// Check if that line contains any registered command expression if so return true and the found command expression
		// If not return false
		for (std::string cmdExpression : cmdExpressions) {
			if (a_line.find(cmdExpression) != std::string::npos) {
				a_foundCmdExpression = cmdExpression;
				return true;
			}
		}
		return false;
	}

	bool ScriptFile::doesLineContainLogicExpression(std::string a_line, std::string & a_foundLogicExpression)
	{
		for (std::string logicExpression : logicExpressions) {
			if (a_line.find(logicExpression) != std::string::npos) {
				a_foundLogicExpression = logicExpression;
				return true;
			}
		}
	}

} }
