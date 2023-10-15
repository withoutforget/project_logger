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

/*
#include <iostream>

#include <string>
#include <stdexcept>
#include <memory>
#include <format>




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
	void output(const T& v) { std::wcout << v << std::endl;  }
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

enum class log_level {
	null,
	def,
	warn,
	debug,
	info
};

template<typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Allocator = std::allocator<CharT>>
class formatter {
public:
	using string_type = std::basic_string<CharT, Traits, Allocator>;
	virtual ~formatter() = default;
protected:
	template<typename T1, typename T2>
	auto string_cast(const T1& from) {
		T2 ret{};
		ret.reserve(from.size());
		for (auto el : from)
			ret.push_back(static_cast<T2::value_type>(el));
		return ret;
	}
protected:
	string_type level_to_string(log_level l) {
		using enum log_level;
		switch (l) {
		case null:
		case def:
		default:
			return string_cast<std::string, string_type>("LOG");
		case warn:
			return string_cast<std::string, string_type>("WARN");
		case debug:
			return string_cast<std::string, string_type>("DEBUG");
		case info:
			return string_cast<std::string, string_type>("info");
		}
		return string_cast<std::string, string_type>("LOG");
	}
};

template<typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Allocator = std::allocator<CharT>>
	class logger_basic : protected formatter<CharT, Traits, Allocator> {
	public:
		using string_type = std::basic_string<CharT, Traits, Allocator>;
	private:
		handler_ptr<CharT, Traits, Allocator> m_handler;
		log_level m_level{ log_level::null };
	public:
		logger_basic() = default;
		logger_basic(const handler_ptr<CharT, Traits, Allocator>& handler) : m_handler(handler) {}
		logger_basic(handler_ptr<CharT, Traits, Allocator>&& handler) : m_handler(std::move(handler)) {}
		logger_basic(const logger_basic& rhs) : m_handler(rhs.m_handler) {}
		logger_basic(logger_basic&& rhs) noexcept { std::swap(m_handler, rhs.m_handler); }
		~logger_basic() = default;
	public:
		void set_level(log_level level) { m_level = level; }
		log_level get_level() const { return m_level; }
		auto& operator<<(log_level level) { return (set_level(level), *this); }
	public:
		void log(const string_type& text) {
			if (m_handler == nullptr)
				throw std::runtime_error{ "nullptr handler" };
			auto s = this->string_cast<std::string, string_type>("[{}] {}");
			auto formatted_string = std::vformat(s, std::make_format_args(this->level_to_string(m_level), text));
			auto status = m_handler->log(formatted_string);
			// handling of log
		}
};






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

*/

/*

#include <iostream>

#include <string>
#include <streambuf>
#include <memory>
#include <format>


template<typename Str>
class ihandler_basic {
public:
	using Type = Str;
public:
	ihandler_basic() = default;
	virtual ~ihandler_basic() = default;

	virtual int log(const Str&) = 0;
};

template<typename Str>
using handler_ptr = std::shared_ptr<ihandler_basic<Str>>;


template<typename Str>
class console_handler_basic : ihandler_basic<Str> {
public:
	using Type = Str;
	template<typename Str>	requires requires(Str s) { std::cout << s; }
	void output(const Str& s) {	std::cout << s << std::endl; }
	template<typename Str>	requires requires(Str s) { std::wcout << s; }
	void output(const Str& s) {	std::wcout << s << std::endl; }
public:
	console_handler_basic() = default;
	virtual ~console_handler_basic() = default;

	int log(const Str& str) override {
		output(str);
	}
};


template<typename Str>
class logger_basic {
private:
	handler_ptr<Str> m_handler;
public:
	void log(const Str& text) {
		m_handler->log(text);
	}
};



int main() {

	return 0;
}



*/