#pragma once

#include<string>
#include<dirent.h>
#include<vector>
#include<fstream>

namespace nano {

	static std::string IMAGE_SUFFIX_ARRAY[] = { "png", "PNG", "jpg", "JPG", "pdf", "PDF" };
	static std::string SOUND_SUFFIX_ARRAY[] = { "wav", "WAV" };

	static bool isSuffixImage(std::string a_subject) {
		for (std::string _x : IMAGE_SUFFIX_ARRAY) {
			if (_x == a_subject)
				return true;
		}
		return false;
	}

	static bool isSuffixSound(std::string a_subject) {
		for (std::string _x : SOUND_SUFFIX_ARRAY) {
			if (_x == a_subject)
				return true;
		}
		return false;
	}

	static std::vector<std::string> getDirectoryEntries(std::string a_dir) {
		std::vector<std::string> returnVector;

		DIR* dirp = opendir(a_dir.c_str());
		struct dirent * dp;
		while ((dp = readdir(dirp)) != NULL) {
			returnVector.push_back(dp->d_name);
		}
		closedir(dirp);

		return returnVector;
	}

	static bool doesFileExist(std::string a_file) {
		std::ifstream fileStream(a_file);
		if (fileStream.is_open()) {
			fileStream.close();
			return true;
		}
		return false;
	}

}