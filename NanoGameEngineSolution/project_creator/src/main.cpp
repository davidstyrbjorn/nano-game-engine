#include<Windows.h>

#include<iostream>
#include<string>

int main()
{
	// Windows.h
	// CopyFile seems to work for both .exe and .txt files which is enough for this case
	// @ TODO find a function for max & linux

	const std::string inputPrompts[] = { "path: " };
	const std::string welcomePrompts[] = { "Welcome to the Nano Game Engine project creator", "Please enter the path for the new prject" };
	std::cout << welcomePrompts[0] << std::endl;
	std::cout << welcomePrompts[1] << std::endl;

	std::cout << inputPrompts[0];
	std::string path;
	std::cin >> path;
	std::cout << std::endl;
	
	system("pause>null");
	return 0;
}