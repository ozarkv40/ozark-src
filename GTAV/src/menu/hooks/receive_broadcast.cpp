#include "hooks.h"
#include "menu/base/util/helpers.h"
#include "rage/types/global_types.h"
#include "util/caller.h"
#include "util/log.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"

static localization t_drop_kick("Drop Kick", true, true);
static localization t_is_being_drop_kicked_by("is being drop kicked by", true, true);
static localization t_array_crash1("Array Crash 1", true, true);
static localization t_array_crash2("Array Crash 2", true, true);
static localization t_array_crash3("Array Crash 3", true, true);
static localization t_array_crash4("Array Crash 4", true, true);
static localization t_array_crash5("Array Crash 5", true, true);

bool notify_crash(localization str, rage::network::net_game_player* sender) {
	if (menu::helpers::is_valid_net_player(sender)) {
		if (protection::events::vars::m_vars.m_crashing.notify()) {
			menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(str), false, true);
		}

		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
	}

	return false;
}

bool menu::hooks::receive_broadcast(uint64_t _this, rage::network::net_game_player* sender, rage::bit_buffer* bit_buffer, uint32_t bit_count, uint16_t network_id) {
	if (menu::helpers::is_valid_net_player(sender)) {
		if (menu::player::get_player(sender->m_id).m_blacklist > GetTickCount()) {
			return false;
		}
	}

	bool drop_kick = false;
	uint64_t drop_kick_backup[33];

	void* drop_kick_ptr = &global::vars::g_global_cache[rage::global::host_drop_kick >> 18 & 0x3F][rage::global::host_drop_kick & 0x3FFFF];
	if (*(uint64_t*)(_this + 0x108) == (uint64_t)drop_kick_ptr) {
		drop_kick = true;
		memcpy(drop_kick_backup, drop_kick_ptr, sizeof(drop_kick_backup));
	}

	uint32_t cached_next_bit = bit_buffer->m_next_bit;
	uint32_t next = 0;
	uint32_t v20 = 0;
	bool v10 = true;

	uint64_t vtable = *(uint64_t*)_this;
	bool unk = caller::call<bool>(*(uint64_t*)(vtable + 0x158), _this);

	for (uint32_t i = bit_buffer->m_next_bit - cached_next_bit; i < bit_count; i = next - cached_next_bit) {
		uint32_t v14 = bit_buffer->m_next_bit;

		// read nodes and test alignment
		global::vars::g_alignment_tests["RB"].m_block = false;
		global::vars::g_alignment_tests["RB"].m_monitor = true;
		global::vars::g_alignment_tests["RB"].m_thread_id = GetCurrentThreadId();

		caller::call<int>(*(uint64_t*)(vtable + 0x178), _this, bit_buffer, &v20); // reads

		global::vars::g_alignment_tests["RB"].m_monitor = false;
		if (global::vars::g_alignment_tests["RB"].m_block) {
			return notify_crash(t_array_crash5, sender);
		}

		if (!caller::call<bool>(*(uint64_t*)(vtable + 0x180), _this, v20)) {
			return notify_crash(t_array_crash1, sender);
		}

		bool v23 = false;
		bool v16 = false;

		if (unk) {
			if (!bit_buffer->read_bool(&v23)) {
				return notify_crash(t_array_crash2, sender);
			}

			v16 = v23;
		} else {
			v16 = false;
			v23 = false;
		}

		if (!v16) {
			// read nodes and test alignment
			global::vars::g_alignment_tests["RB"].m_block = false;
			global::vars::g_alignment_tests["RB"].m_monitor = true;
			global::vars::g_alignment_tests["RB"].m_thread_id = GetCurrentThreadId();

			caller::call<int>(*(uint64_t*)(vtable + 0x1C0), _this, bit_buffer, v20, 0); // reads

			global::vars::g_alignment_tests["RB"].m_monitor = false;
			if (global::vars::g_alignment_tests["RB"].m_block) {
				return notify_crash(t_array_crash5, sender);
			}

			v16 = v23;
		}

		if (caller::call<bool>(*(uint64_t*)(vtable + 0x1A8), _this, v20, sender, v16)) {
			if (v23) {
				caller::call<int>(*(uint64_t*)(vtable + 0x168), _this, v20);
				caller::call<int>(*(uint64_t*)(vtable + 0x190), _this, v20);
			} else {
				if (caller::call<bool>(*(uint64_t*)(vtable + 0x130), _this)) {
					uint64_t v17 = caller::call<uint64_t>(*(uint64_t*)(vtable + 0x130), _this);
					if (v17) {
						uint64_t VTable2 = *(uint64_t*)v17;
						caller::call<int>(*(uint64_t*)(VTable2 + 0xA0), v17, v20);
					} else {
						return notify_crash(t_array_crash3, sender);
					}
				}

				caller::call<int>(*(uint64_t*)(vtable + 0x1D8), _this, v20, sender);
				caller::call<int>(*(uint64_t*)(vtable + 0x1A0), _this, v20);
			}
		} else {
			v10 = false;
		}

		if (v14 == bit_buffer->m_next_bit) {
			return notify_crash(t_array_crash4, sender);
		}

		next = bit_buffer->m_next_bit;
	}

	caller::call<int>(*(uint64_t*)(vtable + 0x198), _this);
	if (v10 && sender->m_id != -1) {
		*(uint16_t*)(_this + 0x6C + (sender->m_id * 2)) = network_id;
	}

	if (drop_kick) {
		if (protection::events::vars::m_vars.m_sh_kick.enabled()) {
			for (int i = 1; i < 33; i++) {
				uint64_t index = (uint64_t)drop_kick_ptr + (i * 8);
				if (*(int*)(index) != *(int*)&drop_kick_backup[i]) {
					if (*(int*)(index) == 1) {
						if (i - 1 == menu::player::get_local_player().m_id) {
							if (protection::events::vars::m_vars.m_sh_kick.block()) {
								*(int*)(index) = *(int*)&drop_kick_backup[i];
							}

							if (protection::events::vars::m_vars.m_sh_kick.notify()) {
								if (menu::helpers::is_valid_net_player(sender)) {
									menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_drop_kick), false, true);
								}
							}
						} else {
							if (protection::events::vars::m_vars.m_sh_kick.notify()) {
								if (native::network_is_session_active() && native::network_is_in_session()) {
									menu::player::player_context& p = menu::player::get_player(i - 1);
									if (p.m_connected && !p.m_name.empty()) {
										if (menu::helpers::is_valid_net_player(sender)) {
											menu::notify::stacked(TRANSLATE(t_drop_kick), util::va::va("%s %s %s", p.m_name.c_str(), TRANSLATE(t_is_being_drop_kicked_by), sender->m_player_info->m_name), global::ui::g_error);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return v10;
}