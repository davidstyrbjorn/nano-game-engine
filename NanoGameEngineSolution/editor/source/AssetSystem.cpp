#include"../include/systems/AssetSystem.h"

#include<asset\Asset.h>
#include<asset\ImageAsset.h>
#include<asset\SoundAsset.h>
#include<StringHelp.h>

#include<dirent.h>
#include<iostream>

#include<FileHelp.h>

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
			if(isSuffixImage(suffix)){
				// Add found image asset
				asset::ImageAsset* imageAsset = new asset::ImageAsset();
				imageAsset->setFileName(fileName);
				imageAsset->loadNew("resources\\assets\\" + fileName);
				m_imageAssetContainer.push_back(imageAsset);
			}
			else if (isSuffixSound(suffix)) {
				// Add found sound asset
				asset::SoundAsset* soundAsset = new asset::SoundAsset();
				soundAsset->setFileName(fileName);
				soundAsset->loadNew("resources\\assets\\" + fileName);
				m_soundAssetContainer.push_back(soundAsset);
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

	asset::ImageAsset * AssetSystem::getImageAssetByHndl(std::string a_hndl)
	{
		for (asset::ImageAsset* asset : m_imageAssetContainer) {
			if (asset->getFileName() == a_hndl)
				return asset;
		}
	}

	std::vector<asset::ImageAsset*> &AssetSystem::getImageAssetContainer()
	{
		return m_imageAssetContainer;
	}

	std::vector<asset::SoundAsset*> &AssetSystem::getSoundAssetContainer()
	{
		return m_soundAssetContainer;
	}

	asset::ImageAsset * AssetSystem::getHighlightAsset()
	{
		return m_highlightTextureAsset;
	}

	void AssetSystem::newAssetImported(const std::string & a_fileName)
	{
		std::string suffix = getFileSuffix(a_fileName);
		if (isSuffixImage(suffix)) {
			// Add found image asset
			asset::ImageAsset* imageAsset = new asset::ImageAsset();
			imageAsset->setFileName(a_fileName);
			imageAsset->loadNew(a_fileName);
			m_imageAssetContainer.push_back(imageAsset);
		}
		else if (isSuffixSound(suffix)) {
			// Add found sound asset
			asset::SoundAsset* soundAsset = new asset::SoundAsset();
			soundAsset->setFileName(a_fileName);
			soundAsset->loadNew(a_fileName);
			m_soundAssetContainer.push_back(soundAsset);
		}
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