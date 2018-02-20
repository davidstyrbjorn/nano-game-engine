#pragma once

#include<fstream>
#include<iostream>
#include<assert.h>
#include<string>

namespace nano {

// Serializing Starts Here

///////////////////
// 
// 
enum OpenMode {
	NONE = 0x0,
	INPUT = 0x1,	   // >> ifstream default
	OUTPUT = 0x2,	   // << ostream default
	BINARY = 0x3,	   // Opeartions in binary not in text format
	AT_END = 0x4,	   // All text is appended at the end of the file
	TRUNCATE = 0x5	   // Discards content of the file before it is opened
};

static std::ofstream gCurrentOutputFile;
static std::ifstream gCurrentInputFile;

///////////////////
// Opens gCurrentOutputFile at a_filePath
// 
bool OpenOutputFile(std::string a_filePath, int _openMode = OpenMode::NONE)
{
	gCurrentOutputFile.open(a_filePath,
		_openMode == OpenMode::OUTPUT |
		_openMode == OpenMode::BINARY ? std::ios::binary : 0 |
		_openMode == OpenMode::AT_END ? std::ios::app : 0 |
		_openMode == OpenMode::TRUNCATE ? std::ios::trunc : 0
	);
	if (!gCurrentOutputFile.is_open()) {
		return false;
	}
	return true;
}

///////////////////
// Writes a_data into the gCurrentOutputFile
// 
void WriteToFile(std::string a_data, bool a_insertNewLine = false)
{
	if (!gCurrentOutputFile.is_open()){
		return;
	}

	// Write the a_data (text) to the file
	if (a_insertNewLine)
		gCurrentOutputFile << (a_data + "\n").c_str();
	else
		gCurrentOutputFile << a_data.c_str();
}

///////////////////
// Inserts a break line into the gCurrentOutputFile
//
void InsertBlankLine() 
{
	if (!gCurrentOutputFile.is_open()) {
		return;
	}

	gCurrentOutputFile << "\n";
}

///////////////////
// Closes the gCurrentOutputFile
// 
bool CloseOutputFile()
{
	gCurrentOutputFile.close();
	if (gCurrentOutputFile.is_open()) {
		return false;
	}
	return true;
}

// Serialzing Ends Here

// Deserializing Starts Here

///////////////////
// Opens gCurrentInputFile at a_filePath
// 
bool OpenInputFile(std::string a_filePath, int _openMode = OpenMode::NONE)
{
	gCurrentInputFile.open(a_filePath,
		_openMode == OpenMode::INPUT |
		_openMode == OpenMode::BINARY ? std::ios::binary : 0 |
		_openMode == OpenMode::AT_END ? std::ios::app : 0 |
		_openMode == OpenMode::TRUNCATE ? std::ios::trunc : 0
	);
	if (!gCurrentInputFile.is_open()) {
		return false;
	}
	return true;
}

///////////////////
// Gets the whole content of the gCurrentInputFile in std::string form
// 
void GetAllFileContent(std::string &a_string)
{
	if (!gCurrentInputFile.is_open()) {
		return;
	}

	a_string.clear();
	std::string _word;
	while (std::getline(gCurrentInputFile, _word)) {
		a_string += _word + "\n";
	}
}

///////////////////
// Closes gCurrentInputFile 
// 
bool CloseInputFile()
{
	gCurrentInputFile.close();
	if (gCurrentInputFile.is_open()) {
		return false;
	}
	return true;
}

// Deserializing End Here

}