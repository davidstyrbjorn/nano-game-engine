#include"../include/ecs/components/SoundComponent.h"

namespace nano { namespace ecs { 

	SoundComponent::SoundComponent(const char* a_soundFilePath)
	{
		// Loading .wav file
		//int format, size, sampleRate, channel, bps;
		//char* data = loadWAV(a_soundFilePath, channel, sampleRate, bps, size, format);
		
		//m_buffer = new sound::SoundBuffer();
		//m_buffer->setData(format, data, size, sampleRate);
		//m_source = new sound::SoundSource(m_buffer->getBufferId());
	}

}
}