#pragma once
#include <string>

using std::operator""s;


template<typename T2, typename T1>
auto string_cast(const T1& from) {
	T2 ret{};
	ret.reserve(from.size());
	for (auto el : from)
		ret.push_back(static_cast<T2::value_type>(el));
	return ret;
}