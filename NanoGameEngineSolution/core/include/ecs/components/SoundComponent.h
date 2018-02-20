#pragma once

#include"../Component.h"

namespace nano {
	namespace openal {
		class SoundSource;
		class SoundBuffer;
	}
}

namespace nano { namespace ecs { 

	class SoundComponent : public Component {
	private:
		openal::SoundSource *m_source;
		openal::SoundBuffer *m_buffer;
		const char* m_soundPath;
		
	public:
		// Constructor with path to sound to load
		SoundComponent(const char* a_soundFilePath);
		// Empty constructor, creates source but no buffer
		SoundComponent();

		// Destructor
		~SoundComponent();

		void LoadNewSound(const char* a_soundFilePath);

		// Getters
		openal::SoundSource *GetSource();
		const char* GetSoundPath();
	};

} }