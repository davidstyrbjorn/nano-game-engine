#include"../include/systems/AssetSystem.h"

#include<asset\Asset.h>
#include<asset\ImageAsset.h>
#include<asset\SoundAsset.h>
#include<StringHelp.h>

#include<dirent.h>
#include<iostream>

namespace nano { namespace editor {

	void AssetSystem::Start()
	{
		// Read in the highlight texture asset
		m_highlightTextureAsset = new asset::ImageAsset();
		m_highlightTextureAsset->loadNew("resources\\rect.png");

		// Read every asset file from resources\assets\ directory
		std::vector<std::string> _files;
		ReadDirectory("resources\\assets\\", _files);

		for (std::string fileName : _files) {
			std::string suffix = getFileSuffix(fileName);
			// Check for file type
			if (suffix == "png" || suffix == "PNG" || suffix == "jpg" || suffix == "JPG") {
				// Add found image asset
				asset::ImageAsset* imageAsset = new asset::ImageAsset();
				imageAsset->setFileName(fileName);
				imageAsset->loadNew("resources\\assets\\" + fileName);
				m_assetContainer.push_back(imageAsset);
			}
			else if (suffix == "wav") {
				// Add found sound asset
				asset::SoundAsset* soundAsset = new asset::SoundAsset();
				soundAsset->setFileName(fileName);
				soundAsset->loadNew("resources\\assets\\" + fileName);
				m_assetContainer.push_back(soundAsset);
			}
		}
	}

	void AssetSystem::Quit()
	{
		// TODO@:
		// Delete every asset pointer here!
		delete m_highlightTextureAsset;
		std::cout << "Asset system quit correctly" << std::endl;
	}

	std::vector<asset::Asset*>& AssetSystem::getAssetContainer()
	{
		return m_assetContainer;
	}

	asset::ImageAsset * AssetSystem::getHighlightAsset()
	{
		return m_highlightTextureAsset;
	}

	void AssetSystem::Update()
	{

	}

	void AssetSystem::ReadDirectory(const std::string & name, std::vector<std::string>& v)
	{
		DIR* dirp = opendir(name.c_str());
		struct dirent * dp;
		while ((dp = readdir(dirp)) != NULL) {
				v.push_back(dp->d_name);
		}
		closedir(dirp);
	}

} }