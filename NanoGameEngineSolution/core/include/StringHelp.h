#pragma once

#include<sstream>
#include<iomanip>

namespace nano {

	template <typename T>
	std::string to_string_with_precision(const T a_value, const int n = 6)
	{
		std::ostringstream out;
		out << std::setprecision(n) << a_value;
		return out.str();
	}

	template<typename T>
	void remove_space(T &a_subject) 
	{
		T subjectCopy = a_subject;
		a_subject = "";
		for (char c : subjectCopy) {
			if (c != ' ')
				a_subject += c;
		}
	}

	static std::string getFileSuffix(std::string a_subject) 
	{
		int i = a_subject.find_last_of('.');
		return a_subject.substr(i+1);
	}

	static std::string getFileName(std::string a_fullPath) {
		// D:\\path\\to\\image\\image.png
		//                     i
		int i = a_fullPath.find_last_of("\\");
		return a_fullPath.substr(i+1);
	}

}