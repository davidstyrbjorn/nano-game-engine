#pragma once

#include<string>

namespace nano { namespace asset {  

	struct AssetInfo {
		std::string hndl;
		size_t byteSize;
		std::string suffix;
	};

	class Asset {
	public:
		Asset();
		virtual ~Asset();

		// Called for clearing current asset info/data
		virtual void freeData() = 0;

		// Loads new asset file
		virtual void loadNew(std::string a_filePath) = 0;

		// Sets m_fileName
		void setFileName(std::string a_name);

		// Returns m_fileName
		std::string getFileName();

	protected:
		std::string m_fileName;
	};

} }