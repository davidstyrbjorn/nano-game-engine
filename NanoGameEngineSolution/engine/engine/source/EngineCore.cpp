#include"../include/EngineCore.h"

#include<graphics\Window.h>
#include<math\Vector4.h>
#include<graphics\Simple_Renderer.h>

#include<thread>
#include<Windows.h>

#define FIXED_TICK_RATE 30 // ticks per second in the fixed loop
#define FIXED_MS 1000/FIXED_TICK_RATE // ms between each tick

namespace nano { namespace engine {

EngineCore::EngineCore()
{
	init();
}

EngineCore::~EngineCore()
{

}

void EngineCore::shutdown()
{
	// Call shutdown on every system
	m_inputSystem->shutdown();
	m_windowSystem->shutdown();
	m_worldSystem->shutdown();
	m_rendererSystem->shutdown();
	m_levelSystem->shutdown();
	m_assetSystem->shutdown();
}

void EngineCore::init()
{
	// Init every system
	m_engineConfig = EngineConfig::getInstance();
	m_engineConfig->loadProjectInfo();

	m_assetSystem = AssetSystem::getInstance();
	m_assetSystem->start();

	m_windowSystem = WindowSystem::getInstance();
	m_windowSystem->start();

	m_worldSystem = WorldSystem::getInstance();
	m_worldSystem->start();

	m_inputSystem = InputSystem::getInstance();
	m_inputSystem->start();

	m_rendererSystem = RendererSystem::getInstance();
	m_rendererSystem->start();

	m_levelSystem = LevelSystem::getInstance();
	m_levelSystem->start();

	// Start the main loop
	mainLoop();
}

void EngineCore::mainLoop()
{
	Clock fixedLoopTimer;
	Clock temp;
	temp.Reset();
	temp.Start();
	int count = 0;
	fixedLoopTimer.Reset();
	fixedLoopTimer.Start();

	// Enter the main loop
	while (m_windowSystem->getWindow().IsOpen()) 
	{
		// Clear the window for new frame
		m_windowSystem->getWindow().Clear(math::Vector4(0.1f, 0.1f, 0.1f, 0));

		// Regular Update
		m_worldSystem->update();
		m_inputSystem->update();
		// Fixed Update
		if (fixedLoopTimer.GetTicks() >= FIXED_MS) {
			fixedLoop();
			count++;
			fixedLoopTimer.Reset();
		}

		// Reset the renderer for this frame
		m_rendererSystem->getRenderer().Begin();
		// This collects the data to be drawn
		m_rendererSystem->update();
		// Flush the renderer (draw calls get called here)
		m_rendererSystem->getRenderer().Flush();

		// Finish the frame
		m_inputSystem->flushEvents();
		m_windowSystem->getWindow().Display();
	}

	shutdown();
}

void EngineCore::fixedLoop()
{
	// Do everything fixed update-y
	m_worldSystem->fixedUpdate();
}

} }