#pragma once

#include<sstream>
#include<iomanip>
#include<vector>

namespace nano {

	template <typename T>
	std::string to_string_with_precision(const T a_value, const int n = 6)
	{
		std::ostringstream out;
		out << std::setprecision(n) << a_value;
		return out.str();
	}

}