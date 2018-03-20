#pragma once

#include"Asset.h"

namespace nano { namespace asset {  

	struct ImageAssetInfo {
		AssetInfo file; // hndl
						// size
						// suffix
		int width, height;
	};

	class ImageAsset : public Asset {
	public:
		ImageAsset();
		~ImageAsset();

		void freeData() override;
		void loadNew(std::string a_filePath) override;

		void* getImageData();
		ImageAssetInfo getAssetInfo();

	private:
		void* m_imageData;
		ImageAssetInfo m_assetInfo;
	};

} }