#include"../include/asset/SoundAsset.h"

#include"../include/sound/NanoOpenAL.h"
#include"../include/StringHelp.h"

namespace nano { namespace asset {  

	SoundAsset::SoundAsset()
	{

	}

	SoundAsset::~SoundAsset()
	{
		freeData();
	}

	void SoundAsset::freeData()
	{
		delete m_soundData;
	}

	void SoundAsset::loadNew(std::string a_path)
	{
		m_soundData = loadWAV(a_path.c_str(), m_assetInfo.channel, m_assetInfo.sampleRate, m_assetInfo.bps, m_assetInfo.size, m_assetInfo.format);
		m_assetInfo.file.hndl = a_path;
		m_assetInfo.file.suffix = getFileSuffix(a_path);
	}

	void * SoundAsset::getSoundData()
	{
		return m_soundData;
	}

	SoundAssetInfo SoundAsset::getAssetInfo()
	{
		return m_assetInfo;
	}

} }