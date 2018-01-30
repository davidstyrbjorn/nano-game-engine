#include"../include/systems/SoundSystem.h"

#include<sound\SoundContextDevice.h>

#include<iostream>

namespace nano { namespace editor {  

	SoundSystem::SoundSystem() { }
	SoundSystem* SoundSystem::_instance = nullptr;
	SoundSystem* SoundSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new SoundSystem();
		return _instance;
	}

	void SoundSystem::Start()
	{
		m_contextDevice = new openal::ContextDevice();
		m_contextDevice->CreateDevice();
		m_contextDevice->CreateContext();
	}

	void SoundSystem::Update()
	{

	}

	void SoundSystem::Quit()
	{
		delete m_contextDevice;
		std::cout << "Sound System quit correctly" << std::endl;
	}

} }