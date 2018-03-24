#pragma once

#include<fstream>
#include<Windows.h>

namespace nano {

	enum OS {
		WINDOWS,
		UNIX
	};

	static void NANO_CopyFile(const char* a_src, const char* a_dst) {
		//std::ifstream src(a_src, std::ios::binary);
		//std::ofstream dst(a_dst, std::ios::binary);
		//
		//// Perform copy operation
		//dst << src.rdbuf();
		CopyFile(a_src, a_dst, FALSE);

		return void();
	}

}