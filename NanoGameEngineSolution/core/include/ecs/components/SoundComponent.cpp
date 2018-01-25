#include "SoundComponent.h"

#include"../../sound/NanoOpenAL.h"

#include"../../sound/SoundBuffer.h"
#include"../../sound/SoundSource.h"

namespace nano { namespace ecs { 

	SoundComponent::SoundComponent(const char * a_soundFilePath)
	{
		int format, size, sampleRate, channel, bps;
		char* data = loadWAV(a_soundFilePath, channel, sampleRate, bps, size, format);

		m_buffer = new openal::SoundBuffer();
		m_buffer->SetData(format, data, size, sampleRate);
		m_source = new openal::SoundSource(m_buffer->GetBufferId());
	}

	openal::SoundSource * nano::ecs::SoundComponent::GetSource()
	{
		return m_source;
	}

} } 