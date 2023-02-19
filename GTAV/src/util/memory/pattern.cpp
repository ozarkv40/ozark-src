#include "pattern.h"
#include "util/log.h"
#include "util/util.h"
#include "menu/init.h"
#include <Psapi.h>

namespace memory {
	uint64_t module_scan(const char* module_name, std::string pattern) {
		MODULEINFO module = {};
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module_name), &module, sizeof(MODULEINFO));

		std::vector<pattern_byte> p;
		std::istringstream iss(pattern);
		std::string w;

		while (iss >> w) {
			if (w.data()[0] == '?') {
				p.push_back(pattern_byte());
			} else if (w.length() == 2 && isxdigit(w.data()[0]) && isxdigit(w.data()[1])) { // Hex
				p.push_back(pattern_byte(w));
			} else {
				return 0;
			}
		}

		for (uint32_t i = 0; i < module.SizeOfImage; i++) {
			uint8_t* current_byte = (uint8_t*)((uint64_t)module.lpBaseOfDll + i);
			bool found = true;

			for (size_t ps = 0; ps < p.size(); ps++) {
				if (!p[ps].m_ignore && current_byte[ps] != p[ps].m_data) {
					found = false;
					break;
				}
			}

			if (found) {
				return (uint64_t)current_byte;
			}
		}

		return 0;
	}

	void scan(std::string name, std::function<bool(uint64_t)> callback, bool& out) {
		pattern_info& pattern = global::auth::g_signatures[name];
		if (pattern.m_pattern.empty()) {
			LOG_CUSTOM_WARN("Signature", "Failed to find %s (SRV)", name.c_str());
			out = false;
			return;
		}

		if (!out) {
			pattern.reset();
			return;
		}

		uint64_t address = module_scan(NULL, pattern.m_pattern);
		if (address) {
			LOG_CUSTOM("Signature", "Found %s", pattern.m_name.c_str());
			if (!callback(address + pattern.m_offset)) {
				LOG_CUSTOM_ERROR("Signature", "Failed to process %s", pattern.m_name.c_str());

				if (pattern.m_important) {
					pattern.reset();
					menu::init::unload();
					out = false;
					return;
				}
			}

			pattern.reset();
			out = true;
			return;
		}

		LOG_CUSTOM_WARN("Signature", "Failed to find %s (CLI) \"%s\"", pattern.m_name.c_str(), pattern.m_pattern.c_str());

		if (pattern.m_important) {
			pattern.reset();

			menu::init::unload();
			out = false;
			return;
		}

		pattern.reset();
		out = true;
	}

	void scan(pattern_info pattern, std::function<bool(uint64_t)> callback, bool& out) {
		if (!out) return;

		uint64_t address = module_scan(NULL, pattern.m_pattern);
		if (address) {
			LOG_CUSTOM("Signature", "Found %s", pattern.m_name.c_str());

			if (!callback(address + pattern.m_offset)) {
				LOG_CUSTOM_ERROR("Signature", "Failed to process %s", pattern.m_name.c_str());

				if (pattern.m_important) {
					menu::init::unload();
					out = false;
					return;
				}
			}

			pattern.reset();
			out = true;
			return;
		}

		LOG_CUSTOM_WARN("Signature", "Failed to find %s", pattern.m_name.c_str());

		if (pattern.m_important) {
			pattern.reset();

			menu::init::unload();
			out = false;
			return;
		}

		pattern.reset();
		out = true;
	}

	void scan(std::string module_name, pattern_info pattern, std::function<bool(uint64_t)> callback, bool& out) {
		if (!out) return;

		uint64_t address = module_scan(module_name.c_str(), pattern.m_pattern);
		if (address) {
			LOG_CUSTOM("Signature", "Found %s", pattern.m_name.c_str());
			if (!callback(address + pattern.m_offset)) {
				LOG_CUSTOM_ERROR("Signature", "Failed to process %s", pattern.m_name.c_str());

				if (pattern.m_important) {
					menu::init::unload();
					out = false;
					return;
				}
			}

			pattern.reset();
			out = true;
			return;
		}

		LOG_CUSTOM_WARN("Signature", "Failed to find %s", pattern.m_name.c_str());

		if (pattern.m_important) {
			pattern.reset();

			menu::init::unload();
			out = false;
			return;
		}

		pattern.reset();
		out = true;
	}
}