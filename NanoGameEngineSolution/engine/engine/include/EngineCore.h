#pragma once

#include"WindowSystem.h"
#include"WorldSystem.h"
#include"InputSystem.h"
#include"RendererSystem.h"
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

	// Shutdown engine
	void shutdown();

	// Main engine loop, root of the program
	void mainLoop();

private:
	EngineConfig *m_engineConfig;
	WindowSystem *m_windowSystem;
	InputSystem *m_inputSystem;
	WorldSystem *m_worldSystem;
	RendererSystem *m_rendererSystem;
};

} }