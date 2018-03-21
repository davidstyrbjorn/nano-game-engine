#include "SoundComponent.h"

#include"../../sound/SoundBuffer.h"
#include"../../sound/SoundSource.h"

namespace nano { namespace ecs { 

	SoundComponent::SoundComponent(const char * a_soundFilePath)
	{
		m_soundPath = a_soundFilePath;

		m_soundAsset = new asset::SoundAsset();
		m_soundAsset->loadNew(a_soundFilePath);

		m_buffer = new openal::SoundBuffer();
		m_buffer->SetData(m_soundAsset->getAssetInfo().format, m_soundAsset->getSoundData(), m_soundAsset->getAssetInfo().size, m_soundAsset->getAssetInfo().sampleRate);
		m_source = new openal::SoundSource(m_buffer->GetBufferId());
	}

	SoundComponent::SoundComponent()
	{
		m_source = new openal::SoundSource();
		m_soundAsset = new asset::SoundAsset();
	}

	SoundComponent::~SoundComponent()
	{
		delete m_buffer;
		delete m_source;
	}

	void SoundComponent::LoadNewSound(const char * a_soundFilePath)
	{
		m_soundPath = a_soundFilePath;

		m_soundAsset->freeData();
		m_soundAsset->loadNew(a_soundFilePath);

		if (m_buffer == nullptr) m_buffer = new openal::SoundBuffer();
		m_buffer->SetData(m_soundAsset->getAssetInfo().format, m_soundAsset->getSoundData(), m_soundAsset->getAssetInfo().size, m_soundAsset->getAssetInfo().sampleRate);

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