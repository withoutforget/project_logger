#include <iostream>

#include "logger.hpp"

int main() {
	try {
		auto p = make_handler<console_handler_basic<char>>();
		logger_basic<char> logger(p);
		logger.log("hello world");
	}
	catch (std::exception& e) {
		std::cout << "exception:" << e.what() << std::endl;
	}
}

