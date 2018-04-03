#pragma once

#include<string>

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

}