#include"../include/systems/EditorConfig.h"

#include"../include/systems/EditorWidgetSystem.h"

#include<fstream>
#include<iostream>

namespace nano { namespace editor { 

	EditorConfig* EditorConfig::_instance = nullptr;

	EditorConfig* EditorConfig::Instance() {
		if (_instance == nullptr) {
			_instance = new EditorConfig();
		}
		return _instance;
	}

	void EditorConfig::loadProjectInfo()
	{
		std::ifstream infoFile("nano.txt");
		if (!infoFile.is_open()) {
			EditorWidgetSystem::Instance()->GetEventHandler().AddEvent(BaseEvent(EventTypes::CONSOLE_MESSAGE, "FATAL: CANNOT LOAD NANO.TXT"));
		}

		std::string _word;
		while (std::getline(infoFile, _word)) {
			if (_word.substr(0, 12) == "project_name") {
				m_projectInfo.projectName = _word.substr(13, _word.length());
			}
			else if (_word.substr(0, 6) == "author") {
				m_projectInfo.author = _word.substr(7, _word.length());
			}
			else if (_word.substr(0, 10) == "local_path") {
				m_projectInfo.localPath = _word.substr(11, _word.length());
			}
		}

		infoFile.close();
	}

	EditorConfig::ProjectInfo EditorConfig::getProjectInfo()
	{
		return m_projectInfo;
	}

	const math::Vector2 EditorConfig::getWindowSize()
	{
		return m_windowSize;
	}

	void EditorConfig::setWindowSize(const math::Vector2 & a_windowSize)
	{
		m_windowSize = a_windowSize;
	}

} } 