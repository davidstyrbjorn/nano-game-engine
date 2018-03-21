#pragma once

#include"Asset.h"

namespace nano { namespace asset {

	// @TODO: use stb to load sound files instead of doing it manually you fucking idiot

	struct SoundAssetInfo {
		AssetInfo file;
		int format;
		int size;
		int sampleRate;
		int channel;
		int bps;
	};

	class SoundAsset : public Asset {
	public:
		SoundAsset();
		~SoundAsset();

		void freeData() override;
		void loadNew(std::string a_path) override;

		void* getSoundData();
		SoundAssetInfo getAssetInfo();

	private:
		void* m_soundData;
		SoundAssetInfo m_assetInfo;
	};


} }