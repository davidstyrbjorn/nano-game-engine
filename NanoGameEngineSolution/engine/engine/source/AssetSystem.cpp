#include"../include/AssetSystem.h"

#include<asset\ImageAsset.h>
#include<asset\SoundAsset.h>
#include<asset\AssetUtility.h>

namespace nano { namespace engine {
	
	void AssetSystem::update() { }
	
	void AssetSystem::start()
	{
		// Get assets from folder
		asset::loadAssetsFromFolder("resources\\assets\\", m_imageAssetContainer, m_soundAssetContainer);
	}

	void AssetSystem::shutdown()
	{
		// Delete asset pointers here!
	}

	std::vector<asset::ImageAsset*> &AssetSystem::getImageAssetContainer()
	{
		return m_imageAssetContainer;
	}

	std::vector<asset::SoundAsset*> &AssetSystem::getSoundAssetContainer()
	{
		return m_soundAssetContainer;
	}

	asset::ImageAsset * AssetSystem::getImageAssetByHndl(std::string a_hndl)
	{
		for (asset::ImageAsset* asset : m_imageAssetContainer) {
			if (asset->getFileName() == a_hndl)
				return asset;
		}
	}

	asset::SoundAsset * AssetSystem::getSoundAssetByHndl(std::string a_hndl)
	{
		for (asset::SoundAsset* asset : m_soundAssetContainer) {
			if (asset->getFileName() == a_hndl)
				return asset;
		}
	}

} }