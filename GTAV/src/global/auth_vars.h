#pragma once
#include "stdafx.h"
#include <unordered_map>

struct pattern_info {
	std::string m_pattern;
	int m_offset;
	std::string m_name;
	bool m_important;

	pattern_info() : m_pattern(""), m_offset(0), m_name(""), m_important(false) {}

	pattern_info(std::string p, int o, std::string n, bool b = false) : m_pattern(p), m_offset(o), m_name(n), m_important(b) {}

	void reset() {
		for (std::size_t i = 0; i < m_pattern.length(); i++) m_pattern[i] = 'F';
		for (std::size_t i = 0; i < m_name.length(); i++) m_name[i] = 'F';

		m_pattern.clear();
		m_name.clear();
		m_offset = -1;
		m_important = false;
	}
};

namespace global::auth {
	extern uint8_t g_hardware_id[0x40];
	extern uint8_t g_auth_token[0x20];
	extern std::string g_username;
	extern std::string g_password;
	extern std::string g_build;
	extern uint32_t g_seconds_left;
	extern bool g_has_lifetime;
	extern std::unordered_map<std::string, pattern_info> g_signatures;
	extern uint8_t g_module_digest[0x40];
	extern std::vector<uint8_t> g_pe_header;
	extern bool g_calculated_digest;
}