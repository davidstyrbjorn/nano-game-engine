#include"include/EditorEntryPoint.h"

int main()
{
	nano::editor::EditorEntryPoint *editor = new nano::editor::EditorEntryPoint();

	delete editor;

	return 0;
}