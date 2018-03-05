#pragma once

#include<iostream>

// Singleton class but not a system so it does not inherit from that base class

namespace nano { namespace engine {

	struct ProjectInfo {
		std::string projectName;
		std::string author;
		std::string localPath;
		std::string startupLevel;
	};

	class EngineConfig {
	private:
		EngineConfig() {}
		static EngineConfig* _instance;

		// Configuration Data
		ProjectInfo m_projectInfo;

	public:
		static EngineConfig *getInstance();

		// Project config info
		void loadProjectInfo();
		ProjectInfo getProjectInfo();
	};
	
} }