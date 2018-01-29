#include"../include/sound/SoundContextDevice.h"

#include<alc.h>
#include<al.h>

namespace nano { 

	openal::ContextDevice::ContextDevice()
	{
		this->CreateDevice();
		this->CreateContext();
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