#pragma once

#include"../Component.h"

namespace nano {
	namespace openal {
		class SoundSource;
		class SoundBuffer;
	}
	namespace asset {
		class Asset;
	}
}



namespace nano { namespace ecs { 

	class SoundComponent : public Component {
	private:
		openal::SoundSource *m_source;
		openal::SoundBuffer *m_buffer;
		const char* m_soundPath;
		
	public:
		// Empty constructor, creates source but no buffer
		SoundComponent();

		// Destructor
		~SoundComponent();

		bool LoadAsset(asset::Asset *a_assetPtr) override;

		// Getters
		openal::SoundSource *GetSource();
		const char* GetSoundPath();
	};

} }