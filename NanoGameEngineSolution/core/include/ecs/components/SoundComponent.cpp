#include "SoundComponent.h"

#include"../../sound/SoundBuffer.h"
#include"../../sound/SoundSource.h"

#include"../../asset/SoundAsset.h"

namespace nano { namespace ecs { 

	SoundComponent::SoundComponent()
	{
		m_source = new openal::SoundSource();
		m_buffer = new openal::SoundBuffer();
	}

	SoundComponent::~SoundComponent()
	{
		delete m_buffer;
		delete m_source;
	}

	bool SoundComponent::LoadAsset(asset::Asset * a_assetPtr)
	{
		asset::SoundAsset* castAsset = dynamic_cast<asset::SoundAsset*>(a_assetPtr);
		if (castAsset == nullptr) {
			// Failed to cast asset to correct sound format
			return false;
		}
		m_buffer->SetData(castAsset->getAssetInfo().format, castAsset->getSoundData(), castAsset->getAssetInfo().size, castAsset->getAssetInfo().sampleRate);
		m_source->SetBuffer(m_buffer->GetBufferId());

		return true;
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