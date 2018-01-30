#include"../include/sound/SoundContextDevice.h"

#include<alc.h>
#include<al.h>

#include<iostream>

namespace nano { 

	openal::ContextDevice::ContextDevice()
	{

	}

	openal::ContextDevice::~ContextDevice()
	{
		alcSuspendContext(m_context);

		if (!alcCloseDevice(m_device)) {
			// Log error @
			std::cout << "Failed to close OpenAL context" << std::endl;
		}
	}

	void openal::ContextDevice::CreateDevice()
	{
		m_device = alcOpenDevice(nullptr);
	}

	void openal::ContextDevice::CreateContext()
	{
		m_context = alcCreateContext(m_device, nullptr);
		alcMakeContextCurrent(m_context);
	}

}