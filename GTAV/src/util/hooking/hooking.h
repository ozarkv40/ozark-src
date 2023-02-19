#pragma once
#include "stdafx.h"
#include "minhook.h"
#include "util/log.h"
#include "util/memory/memory.h"
#include <vector>
#include <random>

namespace hooking {
#define HOOK_SIZE 20

	struct detour_context {
		std::pair<std::string, size_t> m_name;
		uint64_t m_address;
		uint8_t m_original[HOOK_SIZE];
		uint8_t m_hooked[HOOK_SIZE];
		uint8_t m_encryption;
	};

	struct virtual_context {
		std::pair<std::string, size_t> m_name;
		uint64_t m_address;
		uint64_t m_original;
		uint8_t m_encryption;
	};

	struct script_context {
		const char* m_script_name;
		uint64_t m_original;
		int m_position;
	};

	class Hooking {
	public:
		template<typename T>
		__declspec(noinline) bool detour(const char* name, uint64_t address, void* function, T** trampoline) {
			MH_STATUS init_status = MH_Initialize();
			if (init_status == MH_OK || init_status == MH_ERROR_ALREADY_INITIALIZED) {
				if (address && function) {
					uint8_t original[HOOK_SIZE];
					memcpy(original, (void*)address, HOOK_SIZE);

					MH_STATUS hook_status = MH_CreateHook((void*)address, function, (void**)trampoline);
					if (hook_status == MH_OK || hook_status == MH_ERROR_ALREADY_CREATED) {
						hook_status = MH_EnableHook((void*)address);
						if (hook_status == MH_OK) {
							std::random_device r;
							std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
							std::mt19937 rng(seed2);
							std::uniform_int_distribution<int> val(0, 255);

							detour_context detour;
							detour.m_name = std::make_pair(std::string(name), strlen(name));
							detour.m_address = address;
							detour.m_encryption = (uint8_t)val(rng);

							memcpy(detour.m_original, original, HOOK_SIZE);
							memcpy(detour.m_hooked, (void*)address, HOOK_SIZE);

							crypt_detour(&detour);
							m_detours.push_back(detour);
							
							LOG_CUSTOM("Hook", "Hooked %s", name);
							return true;
						}
					}
				}
			}

			return false;
		};

		template<typename T>
		__declspec(noinline) bool vmt(const char* name, uint64_t address, int index, void* function, T** trampoline) {
			if (!address || !function) {
				return false;
			}

			uint64_t table = address + (8 * index);
			uint64_t original = *(uint64_t*)table;

			if (*((void**)trampoline) == nullptr) {
				*((void**)trampoline) = (void*)original;
			}

			std::random_device r;
			std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
			std::mt19937 rng(seed2);
			std::uniform_int_distribution<int> val(0, 255);

			virtual_context vmt;
			vmt.m_name = std::make_pair(std::string(name), strlen(name));
			vmt.m_address = table;
			vmt.m_original = original;
			vmt.m_encryption = (uint8_t)val(rng);

			crypt_vmt(&vmt);
			m_vmts.push_back(vmt);

			memory::write(table, (uint64_t)function);

			LOG_CUSTOM("Hook", "Hooked %s", name);
			return true;
		}

		__declspec(noinline) bool script(const char* name, const char* script, uint64_t native, void* function);

		void crypt_detour(detour_context* detour);
		void crypt_vmt(virtual_context* vmt);
		void cleanup();
	private:
		std::vector<script_context> m_scripts;
		std::vector<detour_context> m_detours;
		std::vector<virtual_context> m_vmts;
	};

	Hooking* get_hooking();

	template<typename T>
	inline bool detour(const char* name, uint64_t address, void* function, T** trampoline) {
		return get_hooking()->detour<T>(name, address, function, trampoline);
	}

	template<typename T>
	inline bool vmt(const char* name, uint64_t address, int index, void* function, T** trampoline) {
		return get_hooking()->vmt<T>(name, address, index, function, trampoline);
	}

	inline bool script(const char* name, const char* script, uint64_t native, void* function) {
		return get_hooking()->script(name, script, native, function);
	}

	inline void cleanup() {
		get_hooking()->cleanup();
	}
}