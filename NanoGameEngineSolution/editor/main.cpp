#include"include/EditorCore.h"

#include<iostream>

int main()
{
	nano::editor::EditorCore* editor = new nano::editor::EditorCore();

	delete editor;

	std::cin.get();
	return 0;
}