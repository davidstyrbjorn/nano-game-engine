#include<Windows.h>

#include<iostream>
#include<string>

#include<fstream>

int main()
{
	// Windows.h
	// CopyFile seems to work for both .exe, .txt and .png files which is enough for this case
	// @ TODO find a function for max & linux
	
	const std::string inputPrompts[] = { "path: ", "name: " };
	const std::string welcomePrompts[] = { 
		"Welcome to the Nano Game Engine project creator", 
		"Please enter the path for the new project ending with a \\",
		"Please enter the name for the new project (no spaces)",
		"Please enter the projects author contact info (email, github name etc) (no spaces)"
	};
	std::cout << welcomePrompts[0] << std::endl;
	std::cout << welcomePrompts[1] << std::endl;

	std::cout << inputPrompts[0];
	std::string path;
	std::cin >> path;

	std::string name;
	std::cout << welcomePrompts[2] << std::endl;;
	std::cout << inputPrompts[1];
	std::cin >> name;
	
	std::string author;
	std::cout << welcomePrompts[3] << std::endl;
	std::cout << inputPrompts[1];
	std::cin >> author;
	
	std::string completeProjectPath = path + name;
#ifdef _WINDOWS_
	CreateDirectory(completeProjectPath.c_str(), NULL);
#endif

	std::ofstream test(completeProjectPath + "\\nano.txt", std::ios::ate);
	/*
	nano.txt
	project_name string
	author string
	local_path string
	*/
	test << "project_name " + name + "\n";
	test << "author " + author + "\n";
	test << "local_path " + completeProjectPath + "\n";

	// Creating directories
	std::string resourceDirectoryPath = completeProjectPath + "\\resources";
#ifdef _WINDOWS_
	CreateDirectory(resourceDirectoryPath.c_str(), NULL);
#endif
	std::string levelsDirectoryPath = resourceDirectoryPath + "\\levels";
#ifdef _WINDOWS_
	CreateDirectory(levelsDirectoryPath.c_str(), NULL);
#endif

	// Copying files
#ifdef _WINDOWS_ // Windows copy functions
	// 1. Image assets
	CopyFile("resources\\rect.png", std::string(completeProjectPath + "\\resources\\rect.png").c_str(), FALSE);
	CopyFile("resources\\error_texture.png", std::string(completeProjectPath + "\\resources\\error_texture.png").c_str(), FALSE);
	// Shaders
	CopyFile("resources\\vertex.txt", std::string(completeProjectPath + "\\resources\\vertex.txt").c_str(), FALSE);
	CopyFile("resources\\fragment.txt", std::string(completeProjectPath + "\\resources\\fragment.txt").c_str(), FALSE);
	// editor.exe
	CopyFile("resources\\editor.exe", std::string(completeProjectPath + "\\editor.exe").c_str(), FALSE);
#endif

	system("pause>null");
}