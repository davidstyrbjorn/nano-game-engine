#pragma once

#include<math\Vector2.h>

namespace nano { namespace editor { 

class EditorConfig {

public:
	struct ProjectInfo {
		std::string projectName;
		std::string author;
		std::string localPath;
	};

private:
	// Singleton closure
	EditorConfig() { }
	static EditorConfig* _instance;

	math::Vector2 m_windowSize;
	ProjectInfo m_projectInfo;

public:
	// Singleton connection
	static EditorConfig* Instance();

	// Loads the neccesary info from the nano.txt file
	void loadProjectInfo();
	ProjectInfo getProjectInfo();

	const math::Vector2 getWindowSize();
	void setWindowSize(const math::Vector2& a_windowSize);

};

} } 