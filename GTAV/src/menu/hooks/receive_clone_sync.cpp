#include "hooks.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/protection/protection_entity_events.h"
#include "menu/base/submenus/main/protection/entity/protection_entity_blocking.h"
#include "menu/base/submenus/main/protection/entity/protection_entity_ghosting.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "util/fiber_pool.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/helpers.h"
#include "util/log.h"
#include "util/caller.h"

static localization t_model_update("Model Update", true, true);

enum eReceiveCloneSync {
	RCS_NOT_IN_ROAMING_BUBBLE = 1,
	RCS_WRONG_OWNER = 2,
	RCS_CANT_APPLY_DATA_NO_NETWORK_OBJECT = 4,
	RCS_CANT_APPLY_DATA = 6,
	RCS_SUCCESS = 8,
};

namespace menu::hooks {
	uint64_t g_rcs_caller_functions[5];
}

int menu::hooks::receive_clone_sync(uint64_t _this, rage::network::net_game_player* sender, uint64_t r8, eNetObjectTypes type, uint16_t network_id, rage::bit_buffer* bit_buffer, uint16_t sequence_id, int timestamp) {
	if (menu::helpers::is_valid_net_player(sender) && sender->m_id != -1) {
		if (sender->m_id < 0 || sender->m_id >= 32) {
			return 69;
		}

		if (menu::player::get_player(sender->m_id).m_blacklist > GetTickCount() && type != NetObjectPlayer) {
			return 69;
		}

		if (protection::entity::vars::m_vars.m_block_modder_sync) {
			if (menu::player::get_player(sender->m_id).m_is_modder) {
				return 69;
			}
		}

		if (menu::player::get_player(sender->m_id).m_block_entities[1][type]) {
			return 69;
		}

		if (menu::player::get_player(sender->m_id).m_ghost[type]
			|| protection::entity::ghosting::vars::m_vars.m_ghosts[type].m_enabled_for_session) {
			return 69;
		}
	} else return receive_clone_sync_t(_this, sender, r8, type, network_id, bit_buffer, sequence_id, timestamp);

	rage::network::sync_tree* tree = rage::engine::get_sync_tree(type);
	if (!is_valid_ptr(tree)) {
		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
		return 69;
	}

	if (tree->m_data_node_count <= 0 || tree->m_data_node_count > 100) {
		if (protection::events::vars::m_vars.m_crashing.notify()) {
			if (menu::helpers::is_valid_net_player(sender)) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_bad_node_count), false, true);
			}
		}

		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
		return 69;
	}

	// read nodes and test alignment
	global::vars::g_alignment_tests["RCS"].m_block = false;
	global::vars::g_alignment_tests["RCS"].m_monitor = true;
	global::vars::g_alignment_tests["RCS"].m_thread_id = GetCurrentThreadId();

	rage::engine::parse_nodes(tree, 2, 0, bit_buffer, 0);

	global::vars::g_alignment_tests["RCS"].m_monitor = false;
	if (global::vars::g_alignment_tests["RCS"].m_block) {
		if (protection::events::vars::m_vars.m_crashing.notify()) {
			if (menu::helpers::is_valid_net_player(sender)) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_nodes), false, true);
			}
		}

		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
		return 69;
	}

	rage::network::net_object* object = rage::engine::get_network_object_from_network_id(_this, network_id, false);
	if (!is_valid_ptr(object)) {
		return RCS_CANT_APPLY_DATA_NO_NETWORK_OBJECT;
	}

	if (object->m_type != type) {
		return RCS_CANT_APPLY_DATA;
	}

	if (protection::events::vars::m_vars.m_attachments.enabled()) {
		bool vehicle_attachment = false;
		uint16_t connected_id = 0;

		if (menu::helpers::is_node_attached(tree->m_parent_node, &vehicle_attachment, &connected_id)) {
			if (menu::helpers::is_valid_net_player(sender)) {
				if (protection::events::vars::m_vars.m_attachments.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, t_attachment.get() + t_attachment_to.get() + (vehicle_attachment ? t_attachment_vehicle.get() : t_attachment_player.get()) + " - " + menu::helpers::get_net_obj_type_string(type), false, protection::events::vars::m_vars.m_attachments.block());
				}

				if (protection::events::vars::m_vars.m_attachments.block()) {
					return RCS_CANT_APPLY_DATA;
				}
			}
		}

		if (connected_id > 0) {
			if (connected_id == network_id) {
				return RCS_CANT_APPLY_DATA;
			}

			rage::network::net_object* object = rage::engine::get_network_object_from_network_id(_this, connected_id, false);
			if (is_valid_ptr(object) && is_valid_ptr(object->m_entity)) {
				;
			} else {
				return RCS_CANT_APPLY_DATA;
			}
		}
	}

	if (type == NetObjectPlayer) {
		if (menu::helpers::is_valid_net_player(sender)) {
			uint64_t appearance = 0;
			menu::helpers::node_foreach(tree->m_parent_node, [&](std::string name, rage::network::data_node* node) {
				if (!name.compare("CPlayerAppearanceDataNode")) {
					if (node->is_data_node() && node->is_writing()) {
						if (node->m_data_node_common_operations) {
							if (node->m_data_node_common_operations->m_data) {
								appearance = node->m_data_node_common_operations->m_data;
							}
						}
					}
				}
			});

			if (is_valid_ptr(appearance)) {
				if (menu::player::get_player(sender->m_id).m_cached_model) {
					uint32_t current_model = native::get_entity_model(native::get_player_ped_script_index(sender->m_id));
					uint32_t model_hash = *(uint32_t*)(appearance + 0x410);

					if (model_hash != 0x0 && current_model != 0x0 && model_hash != current_model) {
						if (global::vars::g_last_synced_player_models[sender->m_id] != model_hash) {
							global::vars::g_last_synced_player_models[sender->m_id] = model_hash;

							menu::helpers::flag_modder(sender->m_id, menu::player::REASON_INVALID_MODEL);

							if (protection::events::vars::m_vars.m_player_model_update.notify()) {
								menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_model_update), false, protection::events::vars::m_vars.m_player_model_update.block());
							}
						}

						*(uint32_t*)(appearance + 0x410) = current_model;
					}
				} else {
					menu::player::get_player(sender->m_id).m_cached_model = true;
					LOG("Cached %s model -> %X", sender->m_player_info->m_name, *(uint32_t*)(appearance + 0x410));
				}
			}
		}
	}

	if (type == NetObjectPed || type == NetObjectPlayer) {
		uint64_t _node = 0;
		menu::helpers::node_foreach(tree->m_parent_node, [&](std::string name, rage::network::data_node* node) {
			if (!name.compare("CPedAppearanceDataNode") || !name.compare("CPlayerAppearanceDataNode")) {
				if (node->is_data_node() && node->is_writing()) {
					if (node->m_data_node_common_operations) {
						if (node->m_data_node_common_operations->m_data) {
							_node = node->m_data_node_common_operations->m_data;
						}
					}
				}
			}
		});

		if (_node) {
			uint32_t ped_player = type == NetObjectPed ? 0xF0 : 0x190;
			uint64_t components = _node + ped_player + 0x38;
			uint32_t bits = *(uint32_t*)(_node + ped_player);

			for (int i = 0; i <= 12; i++) {
				if ((bits & 1) != 0) {
					uint32_t _offset = 4;
					if (*(uint8_t*)(_node + ped_player + 4)) {
						_offset = 7;
					}

					if ((*(uint32_t*)(components + _offset) == 9 || *(uint32_t*)(components + _offset) == 10)
						&& *(uint32_t*)(components + 0x30) == 0
						&& *(uint32_t*)(components + 0x60) == 0
						&& *(uint32_t*)(components - 0x30) == 0) {
						if (protection::events::vars::m_vars.m_crashing.notify()) {
							if (menu::helpers::is_valid_net_player(sender)) {
								menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_outfit), false, true);
							}
						}

						menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT);
						protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
						return RCS_CANT_APPLY_DATA;
					}
				}

				components += 4;
			}
		}
	}

	return receive_clone_sync_t(_this, sender, r8, type, network_id, bit_buffer, sequence_id, timestamp);
}

bool menu::hooks::receive_clone_sync_caller(uint64_t _this, uint64_t rdx) {
	struct sync_data {
		uint32_t _0x80 = 0;
		uint32_t _0x7C = 0;
		uint32_t _0x78 = 0;
		uint16_t _0x74 = 0;
		uint8_t _0x72 = 0;
		uint8_t _0x71 = 0;
		uint32_t _0x70 = 0;
		char _padding[0x4] = { 0, 0, 0, 0 };
		rage::bit_buffer bb; // 0x68
		char m_stack[0x1000];
	}; sync_data v30;

	uint64_t raw_data = *(uint64_t*)(rdx);
	uint32_t raw_size = *(uint32_t*)(rdx + 0x8);
	uint64_t net_player = *(uint64_t*)(rdx + 0x10);
	uint64_t net_receiver = *(uint64_t*)(rdx + 0x18);

	if (!is_valid_ptr(raw_data))
		return false;

	if (!is_valid_ptr(net_player))
		return false;

	if (!is_valid_ptr(net_receiver))
		return false;

	char v31[920];
	uint16_t v32[140];
	int v33[140];
	uint8_t vars18[2];
	uint32_t vars20;

	v30._0x80 = 0;
	v30._0x7C = 0;
	v30._0x78 = 0;
	v30._0x74 = 0;
	v30._0x72 = 0;
	v30._0x70 = 0;
	v30.bb.prepare_sync((uint64_t)v31, 0x38D);

	// read bb data
	if (!caller::call<bool>(g_rcs_caller_functions[0], &v30, raw_data, raw_size, 0))
		return false;

	uint16_t v5 = v30._0x74;
	uint16_t v6 = 0;

	if (*(uint8_t*)(net_player + 0x20) >= 0x20) {
		v6 = 0;
	} else v6 = *(uint16_t*)(_this + (2 * *(uint8_t*)(net_player + 0x20)) + 171928);

	if ((v30._0x74 << 16) - (v6 << 16) <= 0) {
		*(uint16_t*)vars18 = 0;
		vars20 = 3;
		caller::call<void>(g_rcs_caller_functions[1], _this, net_player, net_receiver, v5, 1, 1, (__int64)vars18, (__int64)&vars20);
		return true;
	}

	if (*(uint8_t*)(net_player + 0x20) < 0x20)
		*(uint16_t*)(_this + (2 * *(uint8_t*)(net_player + 0x20)) + 171928) = v30._0x74;

	uint32_t v9 = v30.bb.m_current_bit;
	if ((v30.bb.m_bit_flag & 1) != 0)
		v9 = v30.bb.m_max_bit;

	vars20 = 0;
	uint32_t v10 = 0;
	uint32_t v11 = 0;
	uint32_t v27 = v9;
	uint32_t v28 = 0;
	uint32_t v26 = 0;
	uint32_t v12 = v30.bb.m_next_bit;
	uint32_t v13 = v9 - v12;

	if (v9 - v12 <= 0x23) {
	LABEL_36:
		caller::call<void>(g_rcs_caller_functions[1], _this, net_player, net_receiver, v5, v10, v11, (__int64)v32, (__int64)v33);
		return true;
	}

	uint32_t a2a = 0;
	uint32_t v16 = 0;
	uint8_t v17 = 0;

	while (true) {
		v30._0x78 = v13;
		a2a = 0;
		vars18[0] = 0;

		v30.bb.read_uint(&a2a, 0x20);

		v16 = a2a;
		v17 = *(uint8_t*)(net_player + 0x21); // player id

		if (v17 != 0xFF)
			break;

	LABEL_26:
		v30.bb.read_byte(&vars18[0], 3);
		a2a = 0;

		if (vars18[0]) {
			do {
				v30._0x80 = 0;
				v30._0x7C = 0;
				v30.bb.read_uint(&v30._0x80, 4);
				v30.bb.read_uint(&v30._0x7C, 0xD);

				uint32_t v29 = v30.bb.m_next_bit;
				uint64_t v20 = v30.bb.m_raw_buffer;

				rage::bit_buffer local_bb;
				local_bb.prepare_sync_local(v20 + (v29 >> 3), ((v27 - v29) & 0xFFFFFFF8) + 8, (v29 - (8 * (v29 >> 3))));

				uint16_t v21 = (uint16_t)v30._0x7C; // network id
				uint16_t v25 = v5; // sequence id

				int v22 = receive_clone_sync(*(uint64_t*)_this,
					(rage::network::net_game_player*)net_player,
					net_receiver,
					(eNetObjectTypes)v30._0x80,
					v21,
					&local_bb,
					v25,
					v16);

				v10 = v28;
				if (v28 < 0x80) {
					v32[v28] = v21;
					v33[v28] = v22 == 69 ? RCS_SUCCESS : v22;
					if (v22 != 8 && v22 != 69)
						++v26;
					v10 = ++v28;
				}

				if (v22 == 69) {
					goto LABEL_36;
				}

				uint32_t v23 = local_bb.m_next_bit;
				caller::call<void>(g_rcs_caller_functions[2], &v30.bb, v23 + v29);

				a2a++;
			} while (a2a < (uint32_t)vars18[0]);
			v9 = v27;
		}

		v13 = v9 - v30.bb.m_next_bit;
		if (v13 == v30._0x78 || v13 <= 0x23) {
			v11 = v26;
			goto LABEL_36;
		}
	}

	uint32_t synced_timestamp = *(uint32_t*)(g_rcs_caller_functions[4]);
	uint8_t v14 = *(uint8_t*)(net_player + 0x21);
	caller::call<void>(g_rcs_caller_functions[3], *(uint64_t*)_this, v14, a2a < synced_timestamp ? synced_timestamp - a2a : 0);

	if (vars20)
		goto LABEL_25;

	uint32_t v18 = *(uint32_t*)(_this + (4 * v17) + 172376);
	if (!v18) {
		*(uint32_t*)(_this + (4 * v17) + 172376) = v16;
		goto LABEL_25;
	}

	if (v16 - v18 <= 0x64) {
	LABEL_25:
		vars20 = 1;
		goto LABEL_26;
	}

	return true;
}