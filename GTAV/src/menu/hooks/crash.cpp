#include "hooks.h"
#include "util/log.h"
#include "util/caller.h"
#include "util/util.h"

namespace util {
	uint64_t sub_140F14DF4(uint64_t a1) {
		uint64_t v1; // rdx
		uint64_t v2; // rcx
		uint64_t v3; // rdx
		uint64_t result; // rax

		v1 = *(uint64_t*)(a1 + 80);
		v2 = 0;

		if (v1) {
			v3 = *(uint64_t*)(v1 + 72);
		} else {
			v3 = 0;
		}

		if (v3 && (*(uint32_t*)(v3 + 92) & 0xFu) >= 2)
			result = *(uint64_t*)v3;
		else
			result = 0;
		if (result) {
			if (*(uint8_t*)(result + 40) == 3)
				v2 = result;
			result = v2;
		}

		return result;
	}
}

// added
int menu::hooks::apply_vehicle_data__crash(rage::network::net_object* object, uint64_t node_data) {
	if (*(bool*)(node_data + 0x119)) {
		uint64_t net_obj = *(uint64_t*)((uint64_t)object - 0x1B0);
		if (!is_valid_ptr(net_obj)) {
			LOG("Someone may have just tried to crash you");
			return 0;
		}

		uint64_t vtable = *(uint64_t*)net_obj;
		if (is_valid_vtable(vtable)) {
			if (caller::call<uint64_t>(*(uint64_t*)(vtable + 0x620), net_obj) == 0) {
				LOG("Someone may have just tried to crash you");
				return 0;
			}
		}
	}

	return apply_vehicle_data__crash_t(object, node_data);
}

// added
eThreadState menu::hooks::tick_script_thread__crash(rage::script::gta_thread* _this, uint32_t instruction_count) {
	if (_this->m_is_paused)
		return _this->m_context.m_state;

	eThreadState state = _this->m_context.m_state;

	static uint8_t stack_backup[0xFFFF];
	static uint8_t thread_backup[sizeof(rage::script::gta_thread)];
	static uint8_t handler_backup[sizeof(rage::script::game_script_handler)];

	if (state == STATE_RUNNING && !global::vars::g_freemode_terminated && _this->m_script_hash == joaat("freemode")) {
		memcpy(thread_backup, _this, sizeof(rage::script::gta_thread));
		memcpy(stack_backup, _this->m_stack, _this->m_context.m_stack_size);

		if (_this->m_context.m_stack_size >= 0xFFFF) {
			LOG("BAD STACK SIZE: %i", _this->m_context.m_stack_size);
		}

		if (_this->m_handler) {
			memcpy(handler_backup, _this->m_handler, sizeof(rage::script::game_script_handler));
		}
	}

	eThreadState tick_state = tick_script_thread__crash_t(_this, instruction_count);

	if (tick_state == STATE_KILLED && state == STATE_RUNNING && _this->m_script_hash == joaat("freemode")) {
		if (!global::vars::g_freemode_terminated) {
			tick_state = STATE_RUNNING;

			memcpy(_this, thread_backup, sizeof(rage::script::gta_thread));
			memcpy(_this->m_stack, stack_backup, _this->m_context.m_stack_size);

			if (_this->m_handler) {
				memcpy(_this->m_handler, handler_backup, sizeof(rage::script::game_script_handler));
			}
		} else {
			global::vars::g_freemode_terminated = false;
		}
	}

	return tick_state;
}

// added
uint64_t menu::hooks::attach_trailer__crash(uint64_t trailer, uint16_t flag) {
	uint64_t entity = *(uint64_t*)(trailer + 0x50);
	if (!is_valid_ptr(entity)) {
		LOG("Someone may have just tried to crash you");
		return 0;
	}

	uint64_t draw_handler = *(uint64_t*)(entity + 0x48);
	if (!is_valid_ptr(draw_handler)) {
		LOG("Someone may have just tried to crash you");
		return 0;
	}

	if ((*(uint32_t*)(draw_handler + 0x5C) & 0xF) >= 2) {
		uint64_t trailer_info = *(uint64_t*)draw_handler;
		if (!trailer_info) {
			LOG("Someone may have just tried to crash you");
			return 0;
		}

		uint64_t table = *(uint64_t*)(trailer_info + 0xC48);
		if (!is_valid_ptr(table)) {
			LOG("Someone may have just tried to crash you");
			return 0;
		}

		if (*(uint16_t*)(trailer_info + 0xC50)) {
			for (uint16_t i = 0; i < *(uint16_t*)(trailer_info + 0xC50); i++) {
				uint64_t address = *(uint64_t*)(table + (i * 8));
				if (!is_valid_ptr(address)) {
					LOG("Someone may have just tried to crash you");
					return 0;
				}
			}
		}
	}

	return attach_trailer__crash_t(trailer, flag);
}

// added
uint64_t menu::hooks::attach_trailer_audio__crash(uint64_t audio_entity, uint64_t rdx) {
	if (!is_valid_ptr(audio_entity)) {
		LOG("Someone just tried to crash you with a pasted crash from last gen LOL");
		return 0;
	}

	uint64_t entity = util::sub_140F14DF4(*(uint64_t*)(audio_entity + 0x6C8));
	if (is_valid_ptr(entity)) {
		uint64_t ptr = *(uint64_t*)(entity + 0x970);
		if (!is_valid_ptr(ptr)) {
			LOG("Someone just tried to crash you with a pasted crash from last gen LOL");
			return 0;
		}
	}

	return attach_trailer_audio__crash_t(audio_entity, rdx);
}

// added
void menu::hooks::destruct_script_handler__crash(uint64_t _this) {
	if (global::vars::g_game_script_handler_manager && *(uint64_t*)(global::vars::g_game_script_handler_manager)) {
		if (*(uint8_t*)(*(uint64_t*)(global::vars::g_game_script_handler_manager) + 0x32)) {
			destruct_script_handler__crash_t(_this);
			return;
		}
	}

	LOG("Someone may have just tried to crash you");
}

// added
bool menu::hooks::shit_scripts2__crash(uint64_t rcx, uint16_t dx, uint32_t r8d, bool r9b) {
	uint64_t* v5; // rcx
	uint64_t i; // rbx

	if (!is_valid_ptr(rcx)) {
		LOG("Someone may have just tried to crash you");
		return false;
	}

	v5 = (uint64_t*)(rcx + 0x30);
	if (!is_valid_ptr(v5))
		return false;

	for (i = *v5; i && (*(uint16_t*)(i + 8) != dx || *(uint32_t*)(i + 16) != r8d); i = *(uint64_t*)(i + 24))
		;

	if (!is_valid_ptr(i))
		return false;

	return shit_scripts2__crash_t(rcx, dx, r8d, r9b);
}

// added
uint64_t menu::hooks::shit_scripts__crash(uint64_t rcx, uint64_t rdx) {
	if (!is_valid_ptr(rcx)) {
		LOG("Someone may have just tried to crash you");
		return 0;
	}

	if (*(uint64_t*)rcx != rdx) {
		if (*(uint64_t*)(rcx + 8) != rdx) {
			if (!is_valid_ptr(*(uint64_t*)(rdx + 0x18))) {
				LOG("Someone may have just tried to crash you");
				return 0;
			}

			if (!is_valid_ptr(*(uint64_t*)(rdx + 0x20))) {
				LOG("Someone may have just tried to crash you");
				return 0;
			}
		} else {
			if (!is_valid_ptr(*(uint64_t*)(rcx + 8))) {
				LOG("Someone may have just tried to crash you");
				return 0;
			}
		}
	}

	return shit_scripts__crash_t(rcx, rdx);
}

// added
uint64_t menu::hooks::rid0__crash(uint64_t rcx, uint64_t rdx) {
	if (rdx) {
		rage::network::player_info* player = (rage::network::player_info*)(rdx - 0x20);

		if (player->m_rockstar_id == 0) {
			player->m_rockstar_id = 69420;
		}

		if (player->m_identifier.m_rockstar_id == 0) {
			player->m_identifier.m_rockstar_id = 69420;
		}
	}

	return rid0__crash_t(rcx, rdx);
}

// added
uint64_t menu::hooks::sub_140AD8424__crash(uint64_t rcx, int edx, uint32_t r8d) {
	if (!is_valid_ptr(rcx) || !is_valid_ptr(*(uint64_t*)(rcx + 0x100))) {
		LOG("Someone may have just tried to crash you");
		return 0;
	}

	if (edx == 2) {
		if ((*(uint16_t*)(rcx + 0x204) >> 8) == 0xFF && (*(uint16_t*)(rcx + 0x204) & 0xFF) != 0xFF) {
			LOG("Someone may have just tried to crash you");
			return 0;
		}
	}

	return sub_140AD8424__crash_t(rcx, edx, r8d);
}