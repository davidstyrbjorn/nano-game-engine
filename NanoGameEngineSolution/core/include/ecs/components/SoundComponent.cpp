#include "SoundComponent.h"

#include"../../sound/NanoOpenAL.h"

#include"../../sound/SoundBuffer.h"
#include"../../sound/SoundSource.h"

#define DR_MP3_IMPLEMENTATION
#include<dr_mp3.h>

namespace nano { namespace ecs { 

	SoundComponent::SoundComponent(const char * a_soundFilePath)
	{
		m_soundPath = a_soundFilePath;

		//int format, size, sampleRate, channel, bps;
		//char* data = loadWAV(a_soundFilePath, channel, sampleRate, bps, size, format);
		drmp3 mp3;
		if (!drmp3_init_file(&mp3, "C:\\temp\\mp3sound.mp3", NULL)) {
			// Failed to open file
		}
		int format = to_al_format(mp3.channels, mp3.sampleRate);
		m_buffer = new openal::SoundBuffer();
		m_buffer->SetData(format, mp3.pData, mp3.dataSize, mp3.sampleRate);
		m_source = new openal::SoundSource(m_buffer->GetBufferId());
	}

	SoundComponent::SoundComponent()
	{
		m_source = new openal::SoundSource();
	}

	SoundComponent::~SoundComponent()
	{
		delete m_buffer;
		delete m_source;
	}

	void SoundComponent::LoadNewSound(const char * a_soundFilePath)
	{
		m_soundPath = a_soundFilePath;

		//int format, size, sampleRate, channel, bps;
		//char* data = loadWAV(a_soundFilePath, channel, sampleRate, bps, size, format);
		drmp3 mp3;
		if (!drmp3_init_file(&mp3, "C:\\temp\\mp3sound.mp3", NULL)) {
			// Failed to open file
		}
		int format = to_al_format(mp3.channels, mp3.sampleRate);
		if (m_buffer == nullptr) m_buffer = new openal::SoundBuffer();
		m_buffer->SetData(format, mp3.pData, mp3.dataSize, mp3.sampleRate);

		m_source->SetBuffer(m_buffer->GetBufferId());
	}

	openal::SoundSource * nano::ecs::SoundComponent::GetSource()
	{
		return m_source;
	}

	const char * SoundComponent::GetSoundPath()
	{
		return m_soundPath;
	}

} } 