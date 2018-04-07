#include"../include/components/ScriptComponentEngine.h"

#include"../include/InputSystem.h"
#include"../include/nsl/ScriptFile.h"

#include<fstream>

namespace nano { namespace engine { 

	ScriptComponent::ScriptComponent(std::string a_hndl)
	{
		m_hndl = a_hndl;
	}

	ScriptComponent::~ScriptComponent()
	{
		delete m_scriptFile;
	}

	void ScriptComponent::Init()
	{
		std::string temp = "resources\\scripts\\" + m_hndl;
		std::ifstream file(temp);
		if (!file.is_open()) {
			std::cout << "Cannot load script file" << std::endl;
		}

		std::vector<std::string> scriptFileContent; // Script file content

		// Read from the file and fill the scriptFileContent 
		std::string line;
		while (std::getline(file, line)) {
			scriptFileContent.push_back(line);
		}
		
		// The file is now read so create the script file object!
		m_scriptFile = new ScriptFile(m_hndl, scriptFileContent);
		m_scriptFile->setTargetEntity(m_owner);
		// Add script as listener for input events
		InputSystem::getInstance()->addInputListener(m_scriptFile);

		// Parse the script file
		m_scriptFile->parseScriptString();
		
	}

	void ScriptComponent::Update()
	{
		m_scriptFile->executeScriptCommands(1.0f);
	}

}} 
