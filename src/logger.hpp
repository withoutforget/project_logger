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

class formatter {
public:
	virtual ~formatter() = default;
public:
	virtual std::string level_to_string(log_level l) {
		using enum log_level;
		switch (l) {
		case null:
		case def:
		default:
			return "LOG";
		case warn:
			return "WARN";
		case debug:
			return "DEBUG";
		case info:
			return "info";
		}
		return "LOG";
	}

};

/*
	TO DO: you have to make a formatter to work level's system bc you have to format any string
*/

template<typename CharT,
		 typename Traits = std::char_traits<CharT>,
	     typename Allocator = std::allocator<CharT>>
class logger_basic {
private:
	template<typename T1, typename T2>
	auto string_cast(const T1& from) {
		T2 ret{};
		ret.reserve(from.size());
		for (auto el : from)
			ret.push_back(static_cast<T2::value_type>(el));
		return ret;
	}
private:
	handler_ptr<CharT, Traits, Allocator> m_handler;
	log_level m_level{ log_level::null };
public:
	std::shared_ptr<formatter> m_formatter = std::make_shared<formatter>();
public:
	logger_basic() = default;
	logger_basic(const handler_ptr<CharT, Traits, Allocator>& handler) : m_handler(handler) {}
	logger_basic(handler_ptr<CharT, Traits, Allocator>&& handler) : m_handler(std::move(handler)) {}
	logger_basic(const logger_basic& rhs) : m_handler(rhs.m_handler) {}
	logger_basic(logger_basic&& rhs) noexcept { std::swap(m_handler, rhs.m_handler); }
	~logger_basic() = default;
public:
	void log(const std::basic_string<CharT, Traits, Allocator>& text) {
		if (m_handler == nullptr)
			throw std::runtime_error{"nullptr handler"};
		auto s = string_cast<std::string,std::basic_string<CharT, Traits, Allocator>>("[{}] {}");
		auto formatted_string = std::vformat(s, std::make_format_args(m_formatter->level_to_string(m_level), text));
		auto status = m_handler->log(formatted_string);
		// handling of log
	}
};

