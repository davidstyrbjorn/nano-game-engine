#include"../include/EngineConfig.h"

#include<iostream>
#include<string>
#include<fstream>

namespace nano { namespace engine {  

	EngineConfig* EngineConfig::_instance = nullptr;
	EngineConfig* EngineConfig::getInstance() {
		if (_instance == nullptr)
			_instance = new EngineConfig();
		return _instance;
	}

	void EngineConfig::loadProjectInfo()
	{
		std::ifstream file("nano.txt");

		std::string _word;
		while (std::getline(file, _word)) {
			if (_word.substr(0, 12) == "project_name") {
				m_projectInfo.projectName = _word.substr(13, _word.length());
			}
			else if (_word.substr(0, 6) == "author") {
				m_projectInfo.author = _word.substr(7, _word.length());
			}
			else if (_word.substr(0, 10) == "local_path") {
				m_projectInfo.localPath = _word.substr(11, _word.length());
			}
			else if (_word.substr(0, 13) == "startup_level") {
				m_projectInfo.startupLevel = _word.substr(14, _word.length());
			}
		}

		file.close();
	}

	ProjectInfo EngineConfig::getProjectInfo()
	{
		return m_projectInfo;
	}

} }