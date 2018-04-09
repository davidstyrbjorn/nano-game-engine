#include"../include/systems/AssetSystem.h"

#include<asset\Asset.h>
#include<asset\ImageAsset.h>
#include<asset\SoundAsset.h>
#include<StringHelp.h>

#include<dirent.h>
#include<iostream>

#include<FileHelp.h>
#include<asset\AssetUtility.h>

namespace nano { namespace editor {

	void AssetSystem::Start()
	{
		// Read in the highlight texture asset
		m_highlightTextureAsset = new asset::ImageAsset();
		m_highlightTextureAsset->loadNew("resources\\rect.png");

		// Read every asset file from resources\assets\ directory
		asset::loadAssetsFromFolder("resources\\assets\\", m_imageAssetContainer, m_soundAssetContainer);
	}

	void AssetSystem::Quit()
	{
		// Delete every asset pointer here!
		std::vector<asset::SoundAsset*>::iterator it1;
		for (it1 = m_soundAssetContainer.begin(); it1 != m_soundAssetContainer.end(); ++it1) {
			delete *it1;
		}
		m_soundAssetContainer.clear();
		std::vector<asset::ImageAsset*>::iterator it2;
		for (it2 = m_imageAssetContainer.begin(); it2 != m_imageAssetContainer.end(); ++it2) {
			delete *it2;
		}
		m_imageAssetContainer.clear();

		delete m_highlightTextureAsset;
		std::cout << "Asset system quit correctly" << std::endl;
	}

	asset::ImageAsset * AssetSystem::getImageAssetByHndl(std::string a_hndl)
	{
		for (asset::ImageAsset* asset : m_imageAssetContainer) {
			if (asset->getFileName() == a_hndl)
				return asset;
		}
		return nullptr;
	}

	std::vector<asset::ImageAsset*> &AssetSystem::getImageAssetContainer()
	{
		return m_imageAssetContainer;
	}

	asset::SoundAsset * AssetSystem::getSoundAssetByHndl(std::string a_hndl)
	{
		for (asset::SoundAsset* asset : m_soundAssetContainer) {
			if (asset->getFileName() == a_hndl)
				return asset;
		}
		return nullptr;
	}

	std::vector<asset::SoundAsset*> &AssetSystem::getSoundAssetContainer()
	{
		return m_soundAssetContainer;
	}

	asset::ImageAsset * AssetSystem::getHighlightAsset()
	{
		return m_highlightTextureAsset;
	}

	void AssetSystem::refresh()
	{
		// Load directory content file names using dirent
		std::vector<std::string> _files;
		DIR* dirp = opendir("resources\\assets\\");
		struct dirent * dp;
		while ((dp = readdir(dirp)) != NULL) {
			_files.push_back(dp->d_name);
		}
		closedir(dirp);

		for (std::string fileName : _files) {
			bool foundAsset = false;
			// Look for asset with fileName
			for (asset::SoundAsset* soundAsset : m_soundAssetContainer) {
				if (fileName == soundAsset->getFileName()) {
					foundAsset = true;
				}
			}
			for (asset::ImageAsset* imageAsset : m_imageAssetContainer) {
				if (fileName == imageAsset->getFileName()) {
					foundAsset = true;
				}
			}
			// Asset inside asset directory is not serialized on our side!
			if (!foundAsset) {
				newAssetImported(fileName);
			}
		}
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

} }