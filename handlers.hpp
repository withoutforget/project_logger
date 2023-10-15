#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include <memory>
#include <iostream>

#ifdef defined(_WIN32) || defined(WIN32) 
#include <Windows.h>
#define FIX_OUTPUT() SetConsoleOutputCP(CP_UTF8)
#else
#define FIX_OUTPUT()
#endif



template<class String>
class basic_ihandler {
public:
	using string_type = String;
	using char_type = typename String::value_type;
	using traits_type = typename String::traits_type;
	using allocator_type = typename String::allocator_type;
public:
	basic_ihandler() = default;
	virtual int log(const String& text) = 0;
	virtual ~basic_ihandler() = default;
};

template<class String>
using handler_ptr = std::shared_ptr<basic_ihandler<String>>;

template<class HandlerType, typename ... Args>
auto make_handler(Args&& ... args) -> handler_ptr<typename HandlerType::string_type> {
	auto p = dynamic_cast<basic_ihandler<typename HandlerType::string_type>*>(new HandlerType(std::forward<Args>(args)...));
	return handler_ptr<typename HandlerType::string_type>(p);
}

template<class String>
class basic_console_handler : public basic_ihandler<String> {
public:
	using string_type = String;
	using char_type = typename String::value_type;
	using traits_type = typename String::traits_type;
	using allocator_type = typename String::allocator_type;
private:
	void output(const String& str) {
		// ain't working for linux
		using char_type = typename String::value_type;			
		std::wbuffer_convert<std::codecvt_utf8<char_type>, char_type> u32buffer(std::cout.rdbuf(), new std::codecvt_utf8<char_type>());
		std::basic_ostream<char_type> out(&u32buffer);
		out << str << std::endl;
	}

public:
	basic_console_handler() {
		FIX_OUTPUT();
	}
	int log(const String& text) override {
		output(text);
		return 0;
	}
	virtual ~basic_console_handler() = default;
};



