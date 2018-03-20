//#include"engine\include\EngineCore.h"

#include<asset\ImageAsset.h>
#include<iostream>

int main()
{
	//nano::engine::EngineCore engine;
	//engine.init();
	nano::asset::ImageAsset imageAsset;
	imageAsset.loadNew("D:\\temp\\cat.png");

	std::cin.get();
	return 0;
}