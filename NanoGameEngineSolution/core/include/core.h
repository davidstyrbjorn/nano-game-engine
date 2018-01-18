#pragma once

#include<string>

namespace nano 
{

// Definitions used in both the editor and the engine side

// Version macros and methods
#define NANO_MAJOR_VERSION 0
#define NANO_MINOR_VERSION 1
static std::string GetWelcomeMessage() { return std::string("Nano Game Engine!\nVersion: " + std::to_string(NANO_MAJOR_VERSION) + "." + std::to_string(NANO_MINOR_VERSION)); }

// Class that both the editor and engine will instantiate, data not shared but both utilize the data and members
// Singleton class
class Core {
private:
	Core() {}
	static Core* _instance;

	float m_targetFPS;

public:
	// Singleton connection
	static Core* Instance();
};

}