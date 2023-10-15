#pragma once

#include <string>
#include <utility>
#include <memory>
#include <stdexcept>
#include <sstream>

#include "handlers.hpp"
#include "utils.hpp"
#include "levels.hpp"

template<class String>
	class basic_logger {
	public:
		using string_type = String;
		using value_type = String::value_type;
		using traits_type = String::traits_type;
		using allocator_type = String::allocator_type;
	private:
		handler_ptr<String> m_handler;
		std::shared_ptr<Ilevel> m_level = std::make_shared<Ilevel>();
	public:
		basic_logger() = default;
		basic_logger(const handler_ptr<String>& handler) : m_handler(handler) {}
		basic_logger(handler_ptr<String>&& handler) : m_handler(std::move(handler)) {}
		basic_logger(const basic_logger& rhs) : m_handler(rhs.m_handler) {}
		basic_logger(basic_logger&& rhs) noexcept { std::swap(m_handler, rhs.m_handler); }
		~basic_logger() = default;
	public:
		void set_level(std::shared_ptr<Ilevel> level) { m_level = level; }
		std::shared_ptr<Ilevel>& get_level() { return m_level; }
		auto& operator<<(std::shared_ptr<Ilevel> level) { return (set_level(level), *this); }
		auto& operator<<(const string_type& text) { return (log(text), *this); }
	public:
		void log(const string_type& text) {
			if (m_handler == nullptr)
				throw std::runtime_error{ "nullptr handler" };
			std::basic_stringstream<value_type, traits_type, allocator_type> ss;
			static auto left_brace = string_cast<string_type>("["s);
			static auto right_brace = string_cast<string_type>("] "s);
			ss << left_brace << get_current_time<string_type>()	<< right_brace;
			ss << left_brace << string_cast<string_type>(m_level->name()) << right_brace;
			ss << left_brace << text << right_brace;
			auto status = m_handler->log(ss.str());
			if (!status)
				throw std::runtime_error{ "Log failed with error "s + std::to_string(status)};
		}
};