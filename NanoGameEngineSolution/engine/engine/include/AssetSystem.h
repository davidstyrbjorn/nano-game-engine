#pragma once

#include"EngineSystemBase.h"

#include<vector>

namespace nano { namespace asset {
	class ImageAsset;
	class SoundAsset;
} }

namespace nano { namespace engine {

	class AssetSystem : public EngineSystemBase<AssetSystem> {
		friend class EngineSystemBase<AssetSystem>;
	private:
		AssetSystem() { }

		std::vector<asset::ImageAsset*> m_imageAssetContainer;
		std::vector<asset::SoundAsset*> m_soundAssetContainer;

	public:
		void start() override;
		void update() override;
		void shutdown() override;

		asset::ImageAsset* getImageAssetByHndl(std::string a_hndl);
		std::vector<asset::ImageAsset*> &getImageAssetContainer();
		asset::SoundAsset* getSoundAssetByHndl(std::string a_hndl);
		std::vector<asset::SoundAsset*> &getSoundAssetContainer();
	};
} }