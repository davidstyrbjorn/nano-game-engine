#include "SoundComponent.h"

#include"../../sound/SoundBuffer.h"
#include"../../sound/SoundSource.h"

#include"../../asset/SoundAsset.h"

namespace nano { namespace ecs { 

	SoundComponent::SoundComponent()
	{
		m_source = new openal::SoundSource();
		m_buffer = new openal::SoundBuffer();
		m_soundAsset = nullptr;
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

		m_soundAsset = castAsset;

		m_buffer->SetData(castAsset->getAssetInfo().format, castAsset->getSoundData(), castAsset->getAssetInfo().size, castAsset->getAssetInfo().sampleRate);
		m_source->SetBuffer(m_buffer->GetBufferId());

		return true;
	}

	asset::SoundAsset * SoundComponent::getSoundAsset()
	{
		return m_soundAsset;
	}

	openal::SoundSource * nano::ecs::SoundComponent::GetSource()
	{
		return m_source;
	}

} } 