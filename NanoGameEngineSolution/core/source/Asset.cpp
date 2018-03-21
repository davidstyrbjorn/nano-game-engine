#include"../include/asset/asset.h"

namespace nano { namespace asset {  

	Asset::Asset() 
	{
		
	}

	Asset::~Asset()
	{

	}

	void Asset::setFileName(std::string a_name)
	{
		m_fileName = a_name;
	}

	std::string Asset::getFileName()
	{
		return m_fileName;
	}

}}