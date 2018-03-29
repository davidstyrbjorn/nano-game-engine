#pragma once

#include<vector>

#include"ImageAsset.h"
#include"SoundAsset.h"
#include"../StringHelp.h"
#include"../FileHelp.h"

#include<dirent.h>

namespace nano { namespace asset {

	static std::string asset_type_to_strig(ASSET_TYPE a_type) {
		if (a_type == ASSET_TYPE::IMAGE)
			return "Image";
		else if (a_type == ASSET_TYPE::SOUND)
			return "Sound";
	}

	static void loadAssetsFromFolder(const std::string &a_dir,
		std::vector<asset::ImageAsset*> &a_imageContainer,
		std::vector<asset::SoundAsset*> &a_soundContainer)
	{
		// Fill the given container of assets from a_dir

		// Load directory content file names using dirent
		std::vector<std::string> _files;
		DIR* dirp = opendir(a_dir.c_str());
		struct dirent * dp;
		while ((dp = readdir(dirp)) != NULL) {
			_files.push_back(dp->d_name);
		}
		closedir(dirp);

		for (std::string file : _files) { 
			std::string suffix = getFileSuffix(file);
			// Check file type
			if (isSuffixImage(suffix)) {
				// Add this image asset
				asset::ImageAsset* _asset = new asset::ImageAsset();
				_asset->setFileName(file);
				_asset->loadNew(a_dir + file);
				a_imageContainer.push_back(_asset);
			}
			else if (isSuffixSound(suffix)) {
				// Add this sound asset
				asset::SoundAsset* _asset = new asset::SoundAsset();
				_asset->setFileName(file);
				_asset->loadNew(a_dir + file);
				a_soundContainer.push_back(_asset);
			}
		}
	}


} }