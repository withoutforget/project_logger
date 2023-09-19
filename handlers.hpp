#pragma once

#include <string>
#include <memory>
#include <iostream>

template<typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Allocator = std::allocator<CharT>>
	class ihandler_basic {
	public:
		using char_type = CharT;
		using traits_type = Traits;
		using allocator_type = Allocator;
	public:
		ihandler_basic() = default;
		virtual int log(const std::basic_string<CharT, Traits, Allocator>& text) = 0;
		virtual ~ihandler_basic() = default;
};

template<typename T, typename ... Args>
auto make_handler(Args&& ... args) {
	using base = ihandler_basic<typename T::char_type, typename T::traits_type, typename T::allocator_type>;
	std::shared_ptr<base> p(dynamic_cast<base*>(new T(std::forward<Args>(args)...)));
	return p;
}

template<typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Allocator = std::allocator<CharT>>
	class console_handler_basic : public ihandler_basic<CharT, Traits, Allocator> {
	public:
		using char_type = CharT;
		using traits_type = Traits;
		using allocator_type = Allocator;
	private:
		template<typename T> requires requires(T v) { std::cout << v; }
		void output(const T& v) { std::cout << v << std::endl; }
		template<typename T> requires requires(T v) { std::wcout << v; }
		void output(const T& v) { std::wcout << v << std::endl; }
	public:
		console_handler_basic() = default;
		int log(const std::basic_string<CharT, Traits, Allocator>& text) override {
			output(text); // here we hope that std::cout or std::wcout can print this string
			return 0;
		}
		virtual ~console_handler_basic() = default;
};

template<typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Allocator = std::allocator<CharT>>
	using handler_ptr = std::shared_ptr<ihandler_basic<CharT, Traits, Allocator>>;