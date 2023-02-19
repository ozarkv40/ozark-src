#include "auth_vars.h"

namespace global::auth {
	uint8_t g_hardware_id[0x40];
	uint8_t g_auth_token[0x20];
	std::string g_username;
	std::string g_password;
	std::string g_build;
	uint32_t g_seconds_left;
	bool g_has_lifetime;
	std::unordered_map<std::string, pattern_info> g_signatures;
	uint8_t g_module_digest[0x40];
	std::vector<uint8_t> g_pe_header;
	bool g_calculated_digest = false;
}