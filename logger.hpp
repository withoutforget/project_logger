#pragma once

#include <string>
#include <utility>
#include <memory>
#include <stdexcept>
#include <format>

#include "handlers.hpp"
#include "utils.hpp"
#include "levels.hpp"

template<typename CharT,
	typename Traits = std::char_traits<CharT>,
	typename Allocator = std::allocator<CharT>>
	class logger_basic {
	public:
		using string_type = std::basic_string<CharT, Traits, Allocator>;
	private:
		handler_ptr<CharT, Traits, Allocator> m_handler;
		std::shared_ptr<Ilevel> m_level = std::make_shared<Ilevel>();
	public:
		logger_basic() = default;
		logger_basic(const handler_ptr<CharT, Traits, Allocator>& handler) : m_handler(handler) {}
		logger_basic(handler_ptr<CharT, Traits, Allocator>&& handler) : m_handler(std::move(handler)) {}
		logger_basic(const logger_basic& rhs) : m_handler(rhs.m_handler) {}
		logger_basic(logger_basic&& rhs) noexcept { std::swap(m_handler, rhs.m_handler); }
		~logger_basic() = default;
	public:
		void set_level(std::shared_ptr<Ilevel> level) { m_level = level; }
		std::shared_ptr<Ilevel>& get_level() { return m_level; }
		auto& operator<<(std::shared_ptr<Ilevel> level) { return (set_level(level), *this); }
	public:
		void log(const string_type& text) {
			if (m_handler == nullptr)
				throw std::runtime_error{ "nullptr handler" };
			auto s = string_cast<string_type>("[{}] {}"s);
			auto formatted_string = std::vformat(s, std::make_format_args(string_cast<string_type>(m_level->name()), text));
			auto status = m_handler->log(formatted_string);

		}
};