#include "hooking.h"
#include "global/vars.h"
#include "rage/invoker/invoker.h"
#include "rage/engine.h"
#include "rage/types/script_types.h"

namespace hooking {
	void Hooking::crypt_detour(detour_context* detour) {
		for (int i = 0; i < detour->m_name.second; i++) {
			detour->m_name.first[i] ^= detour->m_encryption;
		}

		uint8_t* address = (uint8_t*)&detour->m_address;
		for (int i = 0; i < 8; i++) {
			address[i] ^= detour->m_encryption;
		}

		for (int i = 0; i < HOOK_SIZE; i++) {
			detour->m_hooked[i] ^= detour->m_encryption;
			detour->m_original[i] ^= detour->m_encryption;
		}
	}

	void Hooking::crypt_vmt(virtual_context* vmt) {
		for (int i = 0; i < vmt->m_name.second; i++) {
			vmt->m_name.first[i] ^= vmt->m_encryption;
		}

		uint8_t* address = (uint8_t*)&vmt->m_address;
		for (int i = 0; i < 8; i++) {
			address[i] ^= vmt->m_encryption;
		}

		address = (uint8_t*)&vmt->m_original;
		for (int i = 0; i < 8; i++) {
			address[i] ^= vmt->m_encryption;
		}
	}

	void Hooking::cleanup() {
		for (detour_context& detour : m_detours) {
			crypt_detour(&detour);
			MH_QueueDisableHook((void*)detour.m_address);
			LOG_CUSTOM_SUCCESS("Hook", "Unhooked %s", detour.m_name);
		}

		MH_ApplyQueued();
		MH_Uninitialize();

		for (virtual_context& vmt : m_vmts) {
			crypt_vmt(&vmt);
			memory::write(vmt.m_address, vmt.m_original);
			LOG_CUSTOM_SUCCESS("Hook", "Unhooked %s", vmt.m_name);
		}

		for (script_context& script : m_scripts) {
			if (is_valid_ptr(global::vars::g_game_streamed_scripts)) {
				uint64_t table = *(uint64_t*)global::vars::g_game_streamed_scripts;

				int index = 0;
				rage::engine::get_streamed_script_index(&index, script.m_script_name);

				if (index != -1) {
					rage::script::script_header* header = rage::engine::get_script_program(table, index);
					if (is_valid_ptr(header)) {
						header->m_natives[script.m_position] = script.m_original;
						LOG_CUSTOM_SUCCESS("Hook", "Unhooked function in %s", script.m_script_name);
					}
				}
			}
		}
	}

	bool Hooking::script(const char* name, const char* script_name, uint64_t native, void* function) {
		if (is_valid_ptr(global::vars::g_game_streamed_scripts)) {
			uint64_t native_function = (uint64_t)rage::invoker::get_native_handler(native);
			if (is_valid_ptr(native_function)) {
				uint64_t table = *(uint64_t*)global::vars::g_game_streamed_scripts;
				if (is_valid_ptr(table)) {
					int index = 0;
					rage::engine::get_streamed_script_index(&index, script_name);

					if (index != -1) {
						rage::script::script_header* header = rage::engine::get_script_program(table, index);
						if (is_valid_ptr(header)) {
							for (int i = 0; i < header->m_native_count; i++) {
								if (header->m_natives[i] == native_function) {
									header->m_natives[i] = (uint64_t)function;

									script_context script;
									script.m_script_name = script_name;
									script.m_position = i;
									script.m_original = native_function;
									m_scripts.push_back(script);

									LOG_CUSTOM("Hook", "Hooked %s", name);
									return true;
								}
							}
						}
					}
				}
			}
		}

		return false;
	}

	Hooking* get_hooking() {
		static Hooking instance;
		return &instance;
	}
}