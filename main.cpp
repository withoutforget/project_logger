#include <iostream>

#include "logger.hpp"

int main() {
	try {
		auto p = make_handler<basic_console_handler<std::u16string>>();
		basic_logger<std::u16string> logger(p);
		logger.log(u"Привет мир");
	}
	catch (std::exception& e) {
		std::cout << "exception:" << e.what() << std::endl;
	}
}

