#pragma once

#include"WindowSystem.h"
#include"WorldSystem.h"
#include"InputSystem.h"
#include"RendererSystem.h"
#include"LevelSystem.h"
#include"nsl\ScriptingSystem.h"
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
	ScriptingSystem* m_scriptingSystem;
	LevelSystem *m_levelSystem;
	RendererSystem *m_rendererSystem;
};

} }