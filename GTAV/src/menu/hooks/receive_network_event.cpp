#include "hooks.h"
#include "menu/base/util/helpers.h"
#include "util/memory/memory.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/protection/protection_net_events.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "util/fiber_pool.h"
#include "util/log.h"
#include "rage/types/global_types.h"
#include <sstream>

static localization t_vehicle_control("Vehicle Control", true, true);
static localization t_freeze("Freeze", true, true);
static localization t_remove_weapon("Remove Weapon", true, true);
static localization t_remove_weapons("Remove All Weapons", true, true);
static localization t_give_weapon("Give Weapon", true, true);
static localization t_particle_fx("Particle FX", true, true);
static localization t_griefing("Griefing", true, true);
static localization t_game_exploits("Game Exploits", true, true);
static localization t_exploits("Exploits", true, true);
static localization t_cheating("Cheating", true, true);
static localization t_annoying_in_vc("Annoying in VC", true, true);
static localization t_hateful_in_vc("Hateful in VC", true, true);
static localization t_annoying_in_chat("Annoying in Chat", true, true);
static localization t_hateful_in_chat("Hateful in Chat", true, true);
static localization t_being_friendly("Being Friendly", true, true);
static localization t_being_helpful("Being Helpful", true, true);
static localization t_increment_stat("Increment Stat", true, true);
static localization t_explosion_blaming("Explosion - Blaming", true, true);
static localization t_explosion("Explosion", true, true);
static localization t_you("you", true, true);
static localization t_weather("Weather Update", true, true);
static localization t_time_change("Time Change", true, true);
static localization t_crash_invalid_weapon("Crash - Invalid Weapon", true, true);
static localization t_crash_sesce("Crash - SESCE", true, true);
static localization t_crash_task("Crash - Invalid Task", true, true);
static localization t_crash_swse("Crash - SWSE", true, true);
static localization t_crash_weather("Crash - Weather", true, true);
static localization t_crash_clock("Crash - Clock", true, true);
static localization t_sound("Sound", true, true);
static localization t_is_dropping_something("is dropping something", true, true);
static localization t_is_dropping_$("is dropping ~g~$~w~", true, true);
static localization t_is_dropping_rp("is dropping RP", true, true);
static localization t_pickup_spawn_reported("Pickup Spawn Reported", true, true);
static localization t_se("SE", true, true);
static localization t_se_kick_from_ceo("Kick from CEO", true, true);
static localization t_se_ban_from_ceo("Ban from CEO", true, true);
static localization t_se_black_screen("Black Screen", true, true);
static localization t_se_apartment_invite("Apartment Invite", true, true);
static localization t_se_network_bail("Network Bail", true, true);
static localization t_se_set_weather("Set Weather", true, true);
static localization t_se_notification("Notification", true, true);
static localization t_se_crash("Crash", true, true);
static localization t_se_invite("Invite", true, true);
static localization t_se_remove_wanted_level("Remove Wanted Level", true, true);
static localization t_se_cops_turn_blind_eye("Cops Turn Blind Eye", true, true);
static localization t_se_off_the_radar("Off the Radar", true, true);
static localization t_se_vehicle_lock_on("Vehicle Lock On", true, true);
static localization t_se_destroyed_personal_vehicle("Destroyed Personal Vehicle", true, true);
static localization t_se_kick_from_vehicle("Kick from Vehicle", true, true);
static localization t_se_force_into_mission("Force Into Mission", true, true);
static localization t_se_force_into_moc_mission("Force Into MOC Mission", true, true);
static localization t_se_screen_flicker("Screen Flicker", true, true);
static localization t_se_send_to_island("Send to Island", true, true);
static localization t_se_transaction_error("Transaction Error", true, true);

uint64_t get_event_setup(int16_t event_id, uint64_t* out_callback = nullptr) {
	uint64_t table = *(uint64_t*)global::vars::g_network_event_registration;
	if (table) {
		uint64_t callback = *(uint64_t*)(table + (event_id * 8) + 0x3B3D0); // update
		if (callback) {
			uint64_t setup = 0;

			for (int i = 0; i < 0x40; i++) {
				if (*(uint8_t*)(callback + i) == 0xE8) {
					setup = callback + i;
					break;
				}
			}

			if (setup) {
				if (out_callback) *out_callback = setup;
				return memory::read_instruction(setup, 1, 5);;
			}
		}
	}

	return 0;
}

std::string get_increment_stat_hash_name(uint32_t hash, bool* is_report) {
	*is_report = false;

	switch (hash) {
		case 0x9C6A0C42: *is_report = true; return t_griefing.get();
		case 0xCBFD04A4: *is_report = true; return t_game_exploits.get();
		case 0x9F79BA0B: *is_report = true; return t_exploits.get();
		case 0xEC3CE96A: *is_report = true; return t_cheating.get();
		case 0x62EB8C5A: *is_report = true; return t_annoying_in_vc.get();
		case 0x0E7072CD: *is_report = true; return t_hateful_in_vc.get();
		case 0x762F9994: *is_report = true; return t_annoying_in_chat.get();
		case 0xB722D6C0: *is_report = true; return t_hateful_in_chat.get();
		case 0xDAFB10F9: return t_being_friendly.get();
		case 0x893E1390: return t_being_helpful.get();
	}

	std::stringstream stream;
	stream << "0x" << std::hex << hash;
	return stream.str();
}

void send_ack(uint16_t event_id, rage::network::net_game_player* sender, rage::network::net_game_player* receiver, int event_index, int event_bitset) {
	uint64_t setup = get_event_setup(event_id);
	if (setup) {
		uint8_t setup_buffer[0x500];
		caller::call<int>(setup, setup_buffer, 0);

		if (*(uint8_t*)(setup_buffer + 0xA) & 1) {
			rage::engine::send_network_event_reply(*(uint64_t*)global::vars::g_network_event_registration, setup_buffer, sender, receiver, event_index, event_bitset);
		} else {
			rage::engine::send_network_event_ack(*(uint64_t*)global::vars::g_network_event_registration, setup_buffer, sender, receiver, event_index);
		}
	}
}

void fix_scripted_game_event(uint32_t count, int* raw, int* fixed) {
	bool save = true;
	for (uint32_t i = 0; i < count; i++) {
		if (save) {
			fixed[i == 0 ? 0 : i / 2] = raw[i];
		}

		save ^= true;
	}
}

bool handle_script_event(rage::network::net_game_player* sender, std::string name, int count, int* arguments, bool is_crash = false) {
	if (is_crash) {
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
	}

	if (protection::events::net::vars::m_vars.m_script_events.enabled()) {
		if (protection::events::net::vars::m_vars.m_script_events.notify()) {
			menu::notify::protection(sender->m_player_info->m_name, t_se.get() + ": " + name, protection::events::net::vars::m_vars.m_script_events.redirect(), protection::events::net::vars::m_vars.m_script_events.block() || is_crash);
		}

		if (protection::events::net::vars::m_vars.m_script_events.redirect()) {
			util::fiber::pool::add([=] {
				std::vector<int> args(count >> 3);
				for (int i = 0; i < count >> 3; i++) {
					args[i] = arguments[i];
				}

				menu::helpers::trigger_script_event(args, count >> 3, sender->m_id);
			});
		}
	}

	return protection::events::net::vars::m_vars.m_script_events.block() || is_crash;
}

void menu::hooks::receive_network_event(uint64_t _this, rage::network::net_game_player* sender, rage::network::net_game_player* receiver, uint16_t event_id, int event_index, int event_bitset, uint32_t bit_buffer_size, rage::bit_buffer* bit_buffer) {
	rage::bit_buffer cache;
	memcpy(&cache, bit_buffer, sizeof(cache));

	if (!menu::helpers::is_valid_net_player(sender) || sender->m_id == -1) {
		return receive_network_event_t(_this, sender, receiver, event_id, event_index, event_bitset, bit_buffer_size, bit_buffer);
	}

	if (menu::player::get_player(sender->m_id).m_blacklist > GetTickCount()) {
		LOG_DEV("Preventing network event process from %s - blacklisted", sender->m_player_info->m_name);
		return send_ack(event_id, sender, receiver, event_index, event_bitset);
	}

	if (receiver == *(rage::network::net_game_player**)(*(uint64_t*)(global::vars::g_network_player_manager) + 0xE8) // updated
		&& (event_bitset << 0x18) - (*(uint32_t*)(_this + 4 * (sender->m_id + 0x46 * event_index) + 0x458) << 0x18) <= 0) {
		return receive_network_event_t(_this, sender, receiver, event_id, event_index, event_bitset, bit_buffer_size, bit_buffer);
	}

	switch (event_id) {
		case REQUEST_CONTROL_EVENT: {
			uint16_t network_id = 0;
			bit_buffer->read_ushort(&network_id, 0xD);

			if (menu::player::get_local_player().m_in_vehicle) {
				rage::types::vehicle* vehicle = (rage::types::vehicle*)rage::engine::get_entity_address(menu::player::get_local_player().m_vehicle);
				if (is_valid_ptr(vehicle)) {
					rage::network::net_object* object = rage::engine::get_network_object_from_network_id(*(uint64_t*)(global::vars::g_network_object_manager), network_id, true);
					if (is_valid_ptr(vehicle->get_net_obj())) {
						if (object == vehicle->get_net_obj()) {
							if (vehicle->get_net_obj()->m_owner == menu::player::get_local_player().m_id) {
								if (protection::events::net::vars::m_vars.m_vehicle_control.notify()) {
									menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_vehicle_control), false, protection::events::net::vars::m_vars.m_vehicle_control.block());
								}

								if (protection::events::net::vars::m_vars.m_vehicle_control.block()) {
									return send_ack(event_id, sender, receiver, event_index, event_bitset);
								}
							}
						}
					}
				}
			}

			break;
		}

		case NETWORK_CLEAR_PED_TASKS_EVENT: {
			if (protection::events::net::vars::m_vars.m_freeze.notify()) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_freeze), protection::events::net::vars::m_vars.m_freeze.redirect(), protection::events::net::vars::m_vars.m_freeze.block());
			}

			if (protection::events::net::vars::m_vars.m_freeze.redirect()) {
				util::fiber::pool::add([=] {
					native::clear_ped_tasks_immediately(menu::player::get_player(sender->m_id).m_ped);
				});
			}

			if (protection::events::net::vars::m_vars.m_freeze.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case REMOVE_WEAPON_EVENT: {
			uint16_t network_id = 0;
			bit_buffer->read_ushort(&network_id, 0xD);

			uint32_t weapon_hash = 0;
			bit_buffer->read_uint(&weapon_hash, 0x20);

			if (protection::events::net::vars::m_vars.m_remove_weapon.notify()) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_remove_weapon), protection::events::net::vars::m_vars.m_remove_weapon.redirect(), protection::events::net::vars::m_vars.m_remove_weapon.block());
			}

			if (protection::events::net::vars::m_vars.m_remove_weapon.redirect()) {
				util::fiber::pool::add([=] {
					native::remove_weapon_from_ped(menu::player::get_player(sender->m_id).m_ped, weapon_hash);
				});
			}

			if (protection::events::net::vars::m_vars.m_remove_weapon.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			bool valid_weapon = false;
			uint64_t table = *(uint64_t*)global::vars::g_weapon_info.m_list;
			if (table) {
				for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
					rage::types::weapon_info* ptr = (rage::types::weapon_info*) * (uint64_t*)(table + (i * 8));
					if (ptr) {
						if (ptr->m_name_hash == weapon_hash) {
							valid_weapon = true;
							break;
						}
					}
				}
			}

			if (!valid_weapon) {
				if (protection::events::vars::m_vars.m_crashing.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_invalid_weapon), false, true);
				}

				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
				menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case REMOVE_ALL_WEAPONS_EVENT: {
			if (protection::events::net::vars::m_vars.m_remove_all_weapons.notify()) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_remove_weapons), protection::events::net::vars::m_vars.m_remove_all_weapons.redirect(), protection::events::net::vars::m_vars.m_remove_all_weapons.block());
			}

			if (protection::events::net::vars::m_vars.m_remove_all_weapons.redirect()) {
				util::fiber::pool::add([=] {
					native::remove_all_ped_weapons(menu::player::get_player(sender->m_id).m_ped, true);
				});
			}

			if (protection::events::net::vars::m_vars.m_remove_all_weapons.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case GIVE_WEAPON_EVENT: {
			uint16_t network_id = 0;
			bit_buffer->read_ushort(&network_id, 0xD);

			uint32_t weapon_hash = 0;
			bit_buffer->read_uint(&weapon_hash, 0x20);

			int ammo_count = -1;
			bit_buffer->read_int(&ammo_count, 0x10);

			if (protection::events::net::vars::m_vars.m_give_weapon.notify()) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_give_weapon), false, protection::events::net::vars::m_vars.m_vehicle_control.block());
			}

			if (protection::events::net::vars::m_vars.m_give_weapon.redirect()) {
				util::fiber::pool::add([=] {
					native::give_delayed_weapon_to_ped(menu::player::get_player(sender->m_id).m_ped, weapon_hash, 0, true);
					native::set_ped_ammo(menu::player::get_player(sender->m_id).m_ped, weapon_hash, ammo_count, 0);
				});
			}

			if (protection::events::net::vars::m_vars.m_give_weapon.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			bool valid_weapon = false;
			uint64_t table = *(uint64_t*)global::vars::g_weapon_info.m_list;
			if (table) {
				for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
					rage::types::weapon_info* ptr = (rage::types::weapon_info*)*(uint64_t*)(table + (i * 8));
					if (ptr) {
						if (ptr->m_name_hash == weapon_hash) {
							valid_weapon = true;
							break;
						}
					}
				}
			}

			if (!valid_weapon) {
				if (protection::events::vars::m_vars.m_crashing.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_invalid_weapon), false, true);
				}

				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
				menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case GIVE_CONTROL_EVENT: {
			uint8_t data[0x200];

			if (rage::engine::setup_give_control_event(data, bit_buffer)) {
				if (!*(bool*)(data + 0x42)) {
					int current = 0;

					if (*(int*)(data + 0x48) > 3) {
						return send_ack(event_id, sender, receiver, event_index, event_bitset);
					}

					do {
						uint16_t network_id = *(uint16_t*)(data + 0x54 + (current * 20));
						eNetObjectTypes type = *(eNetObjectTypes*)(data + 0x56 + (current * 20));

						if (type < NetObjectAutomobile || type > NetObjectTrain) {
							return send_ack(event_id, sender, receiver, event_index, event_bitset);
						}

						rage::network::sync_tree* sync_tree = rage::engine::get_sync_tree(type);
						if (!sync_tree) {
							return send_ack(event_id, sender, receiver, event_index, event_bitset);
						}

						if (sync_tree->m_data_node_count == 0 || sync_tree->m_data_node_count > 100) {
							return send_ack(event_id, sender, receiver, event_index, event_bitset);
						}

						rage::network::net_object* object = rage::engine::get_network_object_from_network_id(*(uint64_t*)global::vars::g_network_object_manager, network_id, true);
						if (!object) {
							return send_ack(event_id, sender, receiver, event_index, event_bitset);
						}

						if (object->m_type != type) {
							return send_ack(event_id, sender, receiver, event_index, event_bitset);
						}

						current++;
					} while (current < *(int*)(data + 0x48));
				}
			}

			break;
		}

		case NETWORK_PTFX_EVENT: {
			if (protection::events::net::vars::m_vars.m_particle_fx.notify()) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_particle_fx), false, protection::events::net::vars::m_vars.m_particle_fx.block());
			}

			if (protection::events::net::vars::m_vars.m_particle_fx.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case SCRIPT_ENTITY_STATE_CHANGE_EVENT: {
			uint16_t network_id = 0;
			bit_buffer->read_ushort(&network_id, 0xD);

			uint32_t state_index = 0;
			bit_buffer->read_uint(&state_index, 0x4);

			uint32_t unk = 0;
			bit_buffer->read_uint(&unk, 0x20);

			LOG_DEV("State just came with %i", state_index);

			if (state_index == 6) {
				uint32_t temp;
				bit_buffer->read_uint(&temp, 0xD);

				uint32_t action = 0;
				bit_buffer->read_uint(&action, 0x8);

				if (action >= 16 && action <= 18) {
					if (protection::events::vars::m_vars.m_crashing.notify()) {
						menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_task), false, true);
					}

					protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
					menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
					return send_ack(event_id, sender, receiver, event_index, event_bitset);
				}
			}

			if (state_index > 9) {
				if (protection::events::vars::m_vars.m_crashing.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_sesce), false, true);
				}

				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
				menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case SCRIPT_WORLD_STATE_EVENT: {
			uint32_t state_index = 0;
			bit_buffer->read_uint(&state_index, 0x4);

			bool unk = false;
			bit_buffer->read_bool(&unk);

			if (state_index > 8 || (state_index == 2 && unk)) {
				if (protection::events::vars::m_vars.m_crashing.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_swse), false, true);
				}

				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
				menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case SCRIPTED_GAME_EVENT: {
			uint32_t count = 0;
			bit_buffer->read_uint(&count, 0x20);

			bool block = false;
			int* arguments = new int[54];
			if (count - 1 <= 0x1AF) {
				int padded_arguments[107];
				if (bit_buffer->read_array(padded_arguments, count << 3, 0)) {
					fix_scripted_game_event(count >> 2, padded_arguments, arguments);

					if (arguments[1] >= 0 && arguments[1] <= 32) {
						switch (arguments[0]) {
							case rage::global::ban_from_ceo:
								block = handle_script_event(sender, TRANSLATE(t_se_ban_from_ceo), count, arguments);
								break;

							case rage::global::kick_from_ceo:
								block = handle_script_event(sender, TRANSLATE(t_se_kick_from_ceo), count, arguments);
								break;

							case rage::global::apartment_teleport:
								if ((count >> 3) < 6 || (arguments[4] != arguments[5]) || arguments[4] < 0 || arguments[4] > 116) {
									block = handle_script_event(sender, TRANSLATE(t_se_black_screen), count, arguments);
									break;
								}

								block = handle_script_event(sender, TRANSLATE(t_se_apartment_invite), count, arguments);
								break;

							case rage::global::network_bail:
								block = handle_script_event(sender, TRANSLATE(t_se_network_bail), count, arguments);
								break;

							case rage::global::set_weather:
								block = handle_script_event(sender, TRANSLATE(t_se_set_weather), count, arguments);
								break;

							case rage::global::message_handler:
								block = handle_script_event(sender, TRANSLATE(t_se_notification), count, arguments);
								if (arguments[10] < 0 || arguments[10] > 31) {
									block = handle_script_event(sender, TRANSLATE(t_se_crash), count, arguments, true);
								}

								break;

							case rage::global::invite:
								block = handle_script_event(sender, TRANSLATE(t_se_invite), count, arguments);
								break;

							case rage::global::remove_wanted_level:
								if (menu::player::get_local_player().m_in_vehicle) {
									if (native::is_ped_in_vehicle(menu::player::get_player(sender->m_id).m_ped, menu::player::get_local_player().m_vehicle, true)) {
										block = false;
										break;
									}
								}

								block = handle_script_event(sender, TRANSLATE(t_se_remove_wanted_level), count, arguments);
								break;

							case rage::global::give_cops_turn_blind_eye:
								if (menu::player::get_local_player().m_in_vehicle) {
									if (native::is_ped_in_vehicle(menu::player::get_player(sender->m_id).m_ped, menu::player::get_local_player().m_vehicle, true)) {
										block = false;
										break;
									}
								}

								block = handle_script_event(sender, TRANSLATE(t_se_cops_turn_blind_eye), count, arguments);
								break;

							case rage::global::give_off_the_radar:
								if (menu::player::get_local_player().m_in_vehicle) {
									if (native::is_ped_in_vehicle(menu::player::get_player(sender->m_id).m_ped, menu::player::get_local_player().m_vehicle, true)) {
										block = false;
										break;
									}
								}

								block = handle_script_event(sender, TRANSLATE(t_se_off_the_radar), count, arguments);
								break;

							case rage::global::set_vehicle_can_be_locked_on:
								block = handle_script_event(sender, TRANSLATE(t_se_vehicle_lock_on), count, arguments);
								break;

							case rage::global::destroyed_personal_vehicle:
								block = handle_script_event(sender, TRANSLATE(t_se_destroyed_personal_vehicle), count, arguments);
								break;

							case rage::global::kick_from_vehicle:
								block = handle_script_event(sender, TRANSLATE(t_se_kick_from_vehicle), count, arguments);
								break;

							case rage::global::force_into_mission:
								block = handle_script_event(sender, TRANSLATE(t_se_force_into_mission), count, arguments);
								break;

							case rage::global::_155_sc_crash_1:
								block = handle_script_event(sender, TRANSLATE(t_se_crash), count, arguments, true);
								break;

							case rage::global::_155_sc_crash_2:
								block = handle_script_event(sender, TRANSLATE(t_se_crash), count, arguments, true);
								break;

							case rage::global::_155_sc_crash_3:
								block = true;
								break;

							case rage::global::_155_force_into_moc_mission:
								block = handle_script_event(sender, TRANSLATE(t_se_force_into_moc_mission), count, arguments);
								break;

							case rage::global::_155_screen_flicker:
								block = handle_script_event(sender, TRANSLATE(t_se_screen_flicker), count, arguments);
								break;

							case rage::global::island_teleport:
								block = handle_script_event(sender, TRANSLATE(t_se_send_to_island), count, arguments);
								break;

							case rage::global::_155_transaction_error:
								block = handle_script_event(sender, TRANSLATE(t_se_transaction_error), count, arguments);
								break;
						}
					} else {
						block = true;
					}

					if (block) {
						delete[] arguments;
						return send_ack(event_id, sender, receiver, event_index, event_bitset);
					} else {
						if (arguments[0] > 1000 && arguments[0] < 75000) {
							menu::helpers::flag_modder(sender->m_id, menu::player::REASON_MENU_CHERAX);
						}
					}
				}
			}

			delete[] arguments;
			break;
		}

		case NETWORK_INCREMENT_STAT_EVENT: {
			uint32_t hash = 0;
			bit_buffer->read_uint(&hash, 0x20);

			int value = 0;
			bit_buffer->read_int(&value, 0x20);

			bool is_report = false;
			std::string hash_string = get_increment_stat_hash_name(hash, &is_report);

			if (is_report) {
				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_REPORT, sender->m_id);
			}

			if (protection::events::net::vars::m_vars.m_increment_stat.notify()) {
				menu::notify::protection(sender->m_player_info->m_name, t_increment_stat.get() + " - " + hash_string, false, true);
			}

			if (protection::events::net::vars::m_vars.m_increment_stat.redirect()) {
				rage::engine::send_increment_stat_event(hash, value, sender);
			}

			if (protection::events::net::vars::m_vars.m_increment_stat.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case FIRE_EVENT: {
			if (protection::events::net::vars::m_vars.m_fire.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case EXPLOSION_EVENT: {
			int16_t unk = 0;
			bit_buffer->read_short(&unk, 0x10);
			bit_buffer->read_short(&unk, 0xd);

			int16_t owner_network_id = 0;
			bit_buffer->read_short(&owner_network_id, 0xd);
			bit_buffer->read_short(&unk, 0xd);

			int explosion_type = 0;
			bit_buffer->read_int(&explosion_type, 0x8);

			uint32_t scale = 0;
			bit_buffer->read_uint(&scale, 0x8);

			math::vector3_<float> xyz;
			rage::bit_buffer_sync_instance instance = bit_buffer->create_reader();
			bit_buffer->read_vector3(&instance, &xyz, 0x0, 0x16);

			float fixed_scale = scale * 0.0039215689f;
			float distance = xyz.get_distance(math::vector3<float>::to_serialized(menu::player::get_local_player().m_coords));

			bool dont_notify = false;
			if (protection::events::net::vars::m_vars.m_blame_explosion.notify()) {
				rage::network::net_object* owner_object = rage::engine::get_network_object_from_network_id(*(uint64_t*)(global::vars::g_network_object_manager), owner_network_id, true);
				if (owner_object) {
					if (owner_object->m_owner != sender->m_id) {
						if (owner_object->m_owner >= 0 && owner_object->m_owner < 32) {
							if (menu::player::get_player(owner_object->m_owner).m_connected) {
								dont_notify = true;
								menu::notify::protection(sender->m_player_info->m_name, util::va::va("%s %s", TRANSLATE(t_explosion_blaming), owner_object->m_owner == menu::player::get_local_player().m_id ? TRANSLATE(t_you) : menu::player::get_player(owner_object->m_owner).m_name.c_str()), false, false);
							}
						}
					}
				}
			}

			if (distance <= 2.f || (distance <= 4.f && fixed_scale >= 2.f)) {
				if (protection::events::net::vars::m_vars.m_explosion.notify()) {
					if (!dont_notify) {
						menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_explosion), protection::events::net::vars::m_vars.m_explosion.redirect(), protection::events::net::vars::m_vars.m_explosion.block());
					}
				}

				if (protection::events::net::vars::m_vars.m_explosion.redirect()) {
					util::fiber::pool::add([=] {
						float x = menu::player::get_player(sender->m_id).m_coords.x + fabs(menu::player::get_local_player().m_coords.x - xyz.x);
						float y = menu::player::get_player(sender->m_id).m_coords.y + fabs(menu::player::get_local_player().m_coords.y - xyz.y);
						float z = menu::player::get_player(sender->m_id).m_coords.z + fabs(menu::player::get_local_player().m_coords.z - xyz.z);
						native::add_explosion(x, y, z, explosion_type, fixed_scale, true, false, 1.f, true);
					});
				}
			}

			if (protection::events::net::vars::m_vars.m_explosion.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case NETWORK_PLAY_SOUND_EVENT: {
			bool on_entity = false;
			bit_buffer->read_bool(&on_entity);

			if (on_entity) {
				uint16_t network_id = 0;
				bit_buffer->read_ushort(&network_id, 0xD);

				rage::network::net_object* object = rage::engine::get_network_object_from_network_id(*(uint64_t*)(global::vars::g_network_object_manager), network_id, true);
				if (!object) {
					return send_ack(event_id, sender, receiver, event_index, event_bitset);
				}

				if (global::vars::g_ped_factory && global::vars::g_ped_factory->m_local_ped) {
					if (object->m_entity == (uint64_t)global::vars::g_ped_factory->m_local_ped
						|| object->m_entity == (uint64_t)global::vars::g_ped_factory->m_local_ped->m_vehicle) {
						if (protection::events::net::vars::m_vars.m_sound.notify()) {
							menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_sound), false, protection::events::net::vars::m_vars.m_sound.block());
						}
					}
				}
			} else {
				math::vector3_<float> xyz;
				rage::bit_buffer_sync_instance instance = bit_buffer->create_reader();
				bit_buffer->read_vector3(&instance, &xyz, 0x0, 0x13);

				float distance = xyz.get_distance(math::vector3<float>::to_serialized(menu::player::get_local_player().m_coords));
				if (distance <= 10.f) {
					if (protection::events::net::vars::m_vars.m_sound.notify()) {
						menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_sound), false, protection::events::net::vars::m_vars.m_sound.block());
					}
				}
			}

			if (protection::events::net::vars::m_vars.m_sound.block()) {
				return send_ack(event_id, sender, receiver, event_index, event_bitset);
			}

			break;
		}

		case REPORT_CASH_SPAWN_EVENT: {
			uint64_t peer_token = 0;
			bit_buffer->read_ulonglong(&peer_token, 0x40);

			uint32_t amount = 0;
			bit_buffer->read_uint(&amount, 0x20);

			uint32_t hash = 0;
			bit_buffer->read_uint(&hash, 0x20);

			if (menu::player::get_player(sender->m_id).m_alive) {
				if ((GetTickCount() - protection::events::vars::m_vars.m_money_drop_map[sender->m_id]) > 5000) {
					protection::events::vars::m_vars.m_money_drop_map[sender->m_id] = GetTickCount();

					bool notify = false;
					std::string reason = TRANSLATE(t_is_dropping_something);
					switch (hash) {
						case 0xCE6FDD6B: // Money
						case 0x5DE0AD3E: // Money
						case 0x1E9A99F8: // Money
						case 0x20893292: // Money
						case 0x14568F28: // Money
						case 0x711D02A4: // Money
						case 0xDE78F17E: // Money
						case 0xFE18F3AF: // Money
						case 0x81e70c51: // Money?
						case 0xa1870e82: // Money?
							if (amount > 500 && amount < 3000) {
								notify = true;
								reason = TRANSLATE(t_is_dropping_$) + std::to_string(amount);
								protection::reactions::vars::process_event(protection::reactions::vars::EVENT_MONEY_DROP, sender->m_id);
								menu::helpers::flag_modder(sender->m_id, menu::player::REASON_MONEY_DROP);
							}

							break;

						case 0x2C014CA6: // RP
							notify = true;
							reason = TRANSLATE(t_is_dropping_rp);
							menu::helpers::flag_modder(sender->m_id, menu::player::REASON_RP_DROP);
							break;
					}

					if (protection::events::vars::m_vars.m_pickup_spawning.notify() && notify) {
						menu::notify::stacked(TRANSLATE(t_pickup_spawn_reported), menu::helpers::clean_name(sender->m_player_info->m_name) + " " + reason);
					}
				}
			}

			break;
		}

		case RAGDOLL_REQUEST_EVENT:
		case REMOTE_SCRIPT_LEAVE_EVENT:
		case BLOW_UP_VEHICLE_EVENT:
		case NETWORK_PED_SEEN_DEAD_PED_EVENT:
		case NETWORK_START_SYNCED_SCENE_EVENT:
		case GIVE_PICKUP_REWARDS_EVENT:
		case KICK_VOTES_EVENT: {
			return send_ack(event_id, sender, receiver, event_index, event_bitset);
		}
	}

	memcpy(bit_buffer, &cache, sizeof(cache));
	receive_network_event_t(_this, sender, receiver, event_id, event_index, event_bitset, bit_buffer_size, bit_buffer);
}