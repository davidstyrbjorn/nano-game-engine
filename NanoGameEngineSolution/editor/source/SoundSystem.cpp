#include"../include/systems/SoundSystem.h"

#include<sound\SoundContextDevice.h>

#include<iostream>

namespace nano { namespace editor {  

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