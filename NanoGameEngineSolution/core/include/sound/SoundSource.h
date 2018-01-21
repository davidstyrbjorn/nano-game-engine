#pragma once

/** unsigned 32-bit integer */
typedef unsigned int ALuint;

namespace nano {

	namespace math {
		class Vector3;
	}

namespace openal { 

	enum SoundState {
		PLAYING,
		NOT_PLAYING,
		PAUSED,
	};

	class SoundSource {
	private:
		ALuint m_source;
		SoundState m_soundState;

	public:
		// Constructor
		SoundSource(ALuint a_buffer);

		// Destructor 
		~SoundSource();

		// Property functions ie. alSource()
		void SetVolume(const float a_gain);
		void SetLooping(bool a_loop);
		void SetPitch(const float a_pitch);

		// Getters
		float GetVolume();
		bool IsLooping();
		float GetPitch();
		SoundState GetState();

		// State modify methods 
		void Play();
		void Pause();
		void Continue();
		void Stop();
		void Restart();
	};

} } 