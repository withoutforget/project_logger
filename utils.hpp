#pragma once

#include <string>
#include <ctime>

using std::operator""s;


template<typename T2, typename T1>
constexpr auto string_cast(const T1& from) {
	T2 ret(from.begin(), from.end());
	return ret;
}


template<typename String = std::string>
String get_current_time() {
	auto time = std::time(nullptr);
	auto string = std::ctime(&time);
	auto len = strlen(string);
	String ret{};
	ret.reserve(len);
	for (size_t i = 0; i < len - 1; i++)
		ret.push_back(static_cast<typename String::value_type>(string[i]));
	return ret;
}

