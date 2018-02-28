#include<Windows.h>

#include<iostream>
#include<string>

#include<fstream>

int main()
{
	// Windows.h
	// CopyFile seems to work for both .exe and .txt files which is enough for this case
	// @ TODO find a function for max & linux
	
	const std::string inputPrompts[] = { "path: ", "name: " };
	const std::string welcomePrompts[] = { 
		"Welcome to the Nano Game Engine project creator", 
		"Please enter the path for the new project ending with a \\",
		"Please enter the name for the new project"
	};
	std::cout << welcomePrompts[0] << std::endl;
	std::cout << welcomePrompts[1] << std::endl;

	std::cout << inputPrompts[0];
	std::string path;
	std::cin >> path;

	std::string name;
	std::cout << inputPrompts[1];
	std::cin >> name;
	
	std::string completeProjectPath = path + name;
	CreateDirectory(completeProjectPath.c_str(), NULL);

	std::ofstream test(completeProjectPath + "\\nano.txt", std::ios::ate);
	/*
	nano.txt
	project_name string
	author string
	global_path string
	*/
	test << "project_name " + name + "\n";
	test << "author " + name + "\n";
	test << "global_path " + completeProjectPath + "\n";

	std::string resourceDirectoryPath = completeProjectPath + "\\resources";
	CreateDirectory(resourceDirectoryPath.c_str(), NULL);
	std::string levelsDirectoryPath = resourceDirectoryPath + "\\levels";
	CreateDirectory(levelsDirectoryPath.c_str(), NULL);

	CopyFile("resources//editor.exe", std::string(completeProjectPath + "\\editor.exe").c_str(), FALSE);

	system("pause>null");
	return 0;
}