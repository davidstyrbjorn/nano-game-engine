#include"include/EditorCore.h"

#include<iostream>

using namespace nano::editor;

int main()
{
	EditorCore* editor = new EditorCore();
	delete editor;

	std::cin.get();
	return 0;
}