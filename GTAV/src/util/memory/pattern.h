#pragma once
#include "stdafx.h"
#include "global/auth_vars.h"
#include <sstream>
#include <functional>

namespace memory {
	struct pattern_byte {
		pattern_byte() : m_ignore(true), m_data(0) {};

		pattern_byte(std::string pattern, bool ignore = false) {
			m_data = convert(pattern);
			m_ignore = ignore;
		};

		bool m_ignore;
		uint8_t m_data;
	private:
		uint8_t convert(std::string str) {
			std::istringstream stream(str);
			uint32_t ret = 0;

			if (stream >> std::hex >> ret) {
				return (uint8_t)ret;
			}

			return 0;
		}
	};

	void scan(std::string name, std::function<bool(uint64_t)> callback, bool& out);
	void scan(pattern_info pattern, std::function<bool(uint64_t)> callback, bool& out);
	void scan(std::string module_name, pattern_info pattern, std::function<bool(uint64_t)> callback, bool& out);
}