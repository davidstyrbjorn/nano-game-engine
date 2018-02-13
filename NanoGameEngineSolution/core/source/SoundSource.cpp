#include"../include/sound/SoundSource.h"

#include<alc.h>
#include<al.h>

#include<iostream>

namespace nano { namespace openal {

	SoundSource::SoundSource(ALuint a_buffer)
	{
		alGenSources(1, &m_source);
		if (alGetError() != AL_NO_ERROR) {
			std::cout << "error creating openal audio source" << std::endl;
		}

		// Attatch the sound buffer to this source
		alSourcei(m_source, AL_BUFFER, a_buffer);
		alSourcei(m_source, AL_SOURCE_RELATIVE, AL_TRUE);

		// Initial sound state
		m_soundState = SoundState::NOT_PLAYING;
	}

	SoundSource::SoundSource()
	{
		alGenSources(1, &m_source);
		m_soundState = SoundState::NOT_PLAYING;
	}

	SoundSource::~SoundSource()
	{
		alDeleteBuffers(1, &m_source);
	}

	void SoundSource::SetBuffer(ALuint a_buffer)
	{
		// Attatch the sound buffer to this source
		alSourcei(m_source, AL_BUFFER, a_buffer);
		m_soundState = SoundState::NOT_PLAYING;
	}

	float SoundSource::GetVolume()
	{
		float v = 0;
		alGetSourcef(m_source, AL_GAIN, &v);
		return v;
	}

	bool SoundSource::IsLooping()
	{
		ALint x = 0;
		alGetSourcei(m_source, AL_LOOPING, &x);
		return x;
	}

	float SoundSource::GetPitch()
	{
		float p = 0;
		alGetSourcef(m_source, AL_PITCH, &p);
		return p;
	}

	SoundState SoundSource::GetState()
	{
		return m_soundState;
	}

	void SoundSource::SetVolume(const float a_gain)
	{
		alSourcef(m_source, AL_GAIN, a_gain);
	}

	void SoundSource::SetLooping(bool a_loop)
	{
		alSourcei(m_source, AL_LOOPING, a_loop);
	}

	void SoundSource::SetPitch(const float a_pitch)
	{
		alSourcef(m_source, AL_PITCH, a_pitch);
	}

	void SoundSource::Play()
	{
		alSourcePlay(m_source);
		m_soundState = SoundState::PLAYING;
	}

	void SoundSource::Pause()
	{
		if (m_soundState != (SoundState::PAUSED | SoundState::NOT_PLAYING)) {
			alSourcePause(m_source);
			m_soundState = SoundState::PAUSED;
		}
	}

	void SoundSource::Continue()
	{
		if (m_soundState == SoundState::PAUSED) {
			alSourcePlay(m_source);
			m_soundState = SoundState::PLAYING;
		}
	}

	void SoundSource::Stop()
	{
		if (m_soundState == SoundState::PLAYING) {
			alSourceStop(m_source);
			m_soundState = SoundState::NOT_PLAYING;
		}
	}

	void SoundSource::Restart()
	{
		if (m_soundState != SoundState::NOT_PLAYING) {
			alSourceRewind(m_source);
		}
		if (m_soundState == SoundState::PLAYING) {
			alSourcePlay(m_source);
		}
	}

} }