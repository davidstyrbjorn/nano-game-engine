#pragma once

#include"WindowSystem.h"
#include"EngineConfig.h"

namespace nano { namespace engine {  

class EngineCore {

public:
	// Constructor
	EngineCore() { }

	// Destructor
	~EngineCore();

	// Initalize engine
	void init();

	// Main engine loop, root of the program
	void mainLoop();

private:
	EngineConfig *m_engineConfig;
	WindowSystem *m_windowSystem;

};

} }