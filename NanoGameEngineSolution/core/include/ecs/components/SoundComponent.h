#pragma once

#include"../Component.h"

namespace nano {
	namespace openal {
		class SoundSource;
		class SoundBuffer;
	}
	namespace asset {
		class SoundAsset;
	}
}

namespace nano { namespace ecs { 

	class SoundComponent : public Component {
	private:
		openal::SoundSource *m_source;
		openal::SoundBuffer *m_buffer;
		asset::SoundAsset *m_soundAsset;
		
	public:
		// Empty constructor, creates source but no buffer
		SoundComponent();

		// Destructor
		~SoundComponent();

		bool LoadAsset(asset::Asset *a_assetPtr) override;
		asset::SoundAsset* getSoundAsset();

		// Getters
		openal::SoundSource *GetSource();
	};

} }