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

	//void SoundComponent::LoadNewSound(const char * a_soundFilePath)
	//{
	//	m_soundPath = a_soundFilePath;
	//
	//	m_soundAsset->freeData();
	//	m_soundAsset->loadNew(a_soundFilePath);
	//
	//	if (m_buffer == nullptr) m_buffer = new openal::SoundBuffer();
	//	m_buffer->SetData(m_soundAsset->getAssetInfo().format, m_soundAsset->getSoundData(), m_soundAsset->getAssetInfo().size, m_soundAsset->getAssetInfo().sampleRate);
	//
	//	m_source->SetBuffer(m_buffer->GetBufferId());
	//}

	openal::SoundSource * nano::ecs::SoundComponent::GetSource()
	{
		return m_source;
	}

	const char * SoundComponent::GetSoundPath()
	{
		return m_soundPath;
	}

} } 