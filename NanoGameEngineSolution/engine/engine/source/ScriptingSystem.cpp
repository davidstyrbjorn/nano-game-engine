#include"../include/nsl/ScriptingSystem.h"

#include<dirent.h>
#include<fstream>

namespace nano { namespace engine {

	void ScriptingSystem::readFilesFromDir(std::string a_dir, std::vector<std::string>& a_list)
	{
		DIR* dirp = opendir(a_dir.c_str());
		struct dirent *dp;
		while ((dp = readdir(dirp)) != NULL) {
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
		}
	}

	void ScriptingSystem::update()
	{
		for (ScriptFile script : m_scriptFiles) {
			script.executeScriptCommands();
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