#pragma once

#include <string>

class Ilevel {
public:
	virtual ~Ilevel() = default;
	virtual std::string name() const {
		return "LOG";
	}
};