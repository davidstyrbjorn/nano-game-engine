#pragma once

#include<math\Vector2.h>
#include<math\Vector4.h>

namespace nano { namespace editor { 

class EditorConfig {

public:
	struct ProjectInfo {
		std::string projectName;
		std::string author;
		std::string localPath;
		std::string startupLevel;
	};

private:
	// Singleton closure
	EditorConfig() { }
	static EditorConfig* _instance;

	const int m_majorVersion = 0;
	const int m_minorVersion = 5;

	math::Vector2 m_windowSize;
	math::Vector4 m_clearColor;
	ProjectInfo m_projectInfo;

	std::string m_currentLevelName; // Name of the currently loaded level

public:
	// Singleton connection
	static EditorConfig* Instance();

	const std::string getVersionString();

	// Loads the neccesary info from the nano.txt file
	void loadProjectInfo();
	ProjectInfo getProjectInfo();

	const math::Vector2 getWindowSize();
	void setWindowSize(const math::Vector2& a_windowSize);

	const math::Vector4 getClearColor();
	void setClearColor(const math::Vector4& a_clearColor);

	std::string getCurrentlyLevelName();
	void setCurrentLevelName(std::string a_name);

};

} } 