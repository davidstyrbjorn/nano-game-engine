#include"../include/nsl/ScriptingSystem.h"

#include<dirent.h>
#include<fstream>
#include<iostream>

#include"../include/InputSystem.h"

namespace nano { namespace engine {

	void ScriptingSystem::readFilesFromDir(std::string a_dir, std::vector<std::string>& a_list)
	{
		DIR* dirp = opendir(a_dir.c_str());
		struct dirent *dp;
		while ((dp = readdir(dirp)) != NULL) {
			if(dp->d_name[0] != '.')
				a_list.push_back(dp->d_name);
		}
		closedir(dirp);
	}

	void ScriptingSystem::start()
	{
		// Go through every script file here!
		// & Insert into the scriptFiles vector list 
		std::string dirLocation = "resources\\scripts\\";
		std::vector<std::string> scriptFileNameList;
		readFilesFromDir(dirLocation, scriptFileNameList);

		for (std::string scriptFileName : scriptFileNameList) {
			// Get content from file here 
			std::ifstream file(dirLocation + scriptFileName);
			if (!file.is_open()) {
				std::cout << "Cannot open script file " + dirLocation + scriptFileName << std::endl;
			}
			std::vector<std::string> scriptFileContent; // This is where the file content goes

			// Read from the file and fill the scriptFileContent list
			std::string _word;
			while (std::getline(file, _word)) {
				scriptFileContent.push_back(_word);
			}

			// The file is now read push back to the m_scriptFiles list
			m_scriptFiles.push_back(ScriptFile(scriptFileName.substr(0, scriptFileName.length()-4), scriptFileContent));
		}
	}

	void ScriptingSystem::update(float a_deltaTime)
	{
		for (ScriptFile script : m_scriptFiles) {
			script.executeScriptCommands(a_deltaTime);
		}

		static InputSystem* input = InputSystem::getInstance();
		for (InputEvent event : input->getPolledEvents()) {
			if (event.type == INPUT_TYPE::KEY_PRESSED) {
				m_keysDown[event.key] = true;
			}
			else if (event.type == INPUT_TYPE::KEY_RELEASE) {
				m_keysDown[event.key] = false;
			}
		}
	}

	void ScriptingSystem::shutdown()
	{

	}

	void ScriptingSystem::parseScriptFiles()
	{

	}

	void ScriptingSystem::processScriptCommands()
	{

	}
	
} }