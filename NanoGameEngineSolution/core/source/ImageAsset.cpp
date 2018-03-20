#include"../include/asset/ImageAsset.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../include/stb/stb_image.h"

#include"../include/StringHelp.h"

namespace nano { namespace asset {  

	ImageAsset::ImageAsset()
	{

	}

	ImageAsset::~ImageAsset()
	{
		freeData();
	}

	void ImageAsset::loadNew(std::string a_filePath)
	{
		m_imageData = stbi_load(a_filePath.c_str(), &m_assetInfo.width, &m_assetInfo.height, nullptr, 0);
		m_assetInfo.file.hndl = a_filePath;
		m_assetInfo.file.byteSize = m_assetInfo.width * m_assetInfo.height;
		m_assetInfo.file.suffix = getFileSuffix(a_filePath);
	}

	void * ImageAsset::getImageData()
	{
		return m_imageData;
	}

	ImageAssetInfo ImageAsset::getAssetInfo()
	{
		return m_assetInfo;
	}

	void ImageAsset::freeData() 
	{
		// Do stuff to free image data
		stbi_image_free(m_imageData);
		m_assetInfo.file.byteSize = 0;
	}

} }