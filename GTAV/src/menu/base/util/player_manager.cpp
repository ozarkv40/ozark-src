#include "player_manager.h"
#include "rage/invoker/natives.h"
#include "rage/engine.h"
#include "global.h"
#include "menu/base/submenus/main/network/network_players.h"
#include "menu/base/submenus/main/network/network_recent_players.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "menu/base/submenus/main/network/session/network_session_excludes.h"
#include "menu/base/submenus/main/settings/hide_info.h"
#include "menu/base/util/helpers.h"
#include <algorithm>
#include <random>

static localization t_modder_detection("Modder Detection", true, true);
static localization t_is_modding("is modding", true, true);
static localization t_got_reported("got reported", true, true);
static localization t_is_spoofing_ip("is spoofing their ip to", true, true);
static localization t_is_spoofing_ip_real("their real ip is", true, true);
static localization t_invalid_model("Invalid Model", true, true);
static localization t_spoofed_name("Spoofed name", true, true);
static localization t_spoofed_peer("Spoofed Peer", true, true);
static localization t_spoofed_rid("Spoofed Rockstar ID", true, true);
static localization t_spoofed_ip("Spoofed IP", true, true);
static localization t_crc_flood("CRC Flood", true, true);
static localization t_crc_compromised("CRC Compromised", true, true);
static localization t_crc_not_replied("CRC Not Replied", true, true);
static localization t_info_change1("Info Change 1", true, true);
static localization t_info_change2("Info Change 2", true, true);
static localization t_info_change4("Info Change 4", true, true);
static localization t_info_change5("Info Change 5", true, true);
static localization t_info_change6("Info Change 6", true, true);
static localization t_info_change7("Info Change 7", true, true);
static localization t_arxan("Arxan", true, true);
static localization t_spoofed_chat("Spoofed Chat", true, true);
static localization t_spoofed_text("Spoofed Text", true, true);
static localization t_crash_attempt("Crash Attempt", true, true);
static localization t_weather_change("Weather Change", true, true);
static localization t_spectating("Spectating", true, true);
static localization t_explosive_ammo("Explosive ammo", true, true);
static localization t_explosive_melee("Explosive Melee", true, true);
static localization t_fire_ammo("Fire Ammo", true, true);
static localization t_super_jump("Super Jump", true, true);
static localization t_money_drop("Money Drop", true, true);
static localization t_rp_drop("RP Drop", true, true);
static localization t_quantum_kick("Quantum Kick", true, true);
static localization t_script_migration("Script Migration", true, true);
static localization t_profanity("Profanity", true, true);
static localization t_join_timeout("Join Timeout", true, true);
static localization t_info_mismatch("Info Mismatch", true, true);
static localization t_ghost_player("Ghost", true, true);

namespace menu::player {
	void player_manager::update() {
		for (int i = 0; i < 32; i++) {
			player_context& player = m_players[i];

			player.m_id = i;
			player.m_name = native::get_player_name(i);

			if (i == native::player_id()) {
				player.m_ped = native::player_ped_id();

				if (settings::hide::vars::m_vars.m_hide_names) {
					player.m_name = util::va::va("Player_%i", i);
				}
			} else {
				player.m_ped = native::get_player_ped_script_index(i);
			}

			player.m_exists = native::does_entity_exist(player.m_ped);
			player.m_is_script_host = native::network_get_host_of_script("freemode", -1, 0) == player.m_id;

			if (player.m_net_player == nullptr) player.m_net_player = rage::engine::get_net_game_player(player.m_id);
			player.m_connected = player.m_net_player != nullptr && (uint64_t)native::get_player_name(i) != global::vars::g_invalid_string_address;
			player.m_ped_ptr = (rage::types::ped*)rage::engine::get_entity_address(player.m_ped);

			if (player.m_id == native::player_id()) {
				if (!native::network_is_in_session()) {
					player.m_connected = true;
				}
			}

			if (player.m_exists) {
				if (i == native::player_id()) {
					if (global::vars::g_ped_factory) {
						if (global::vars::g_ped_factory->m_local_ped) {
							if (global::vars::g_ped_factory->m_local_ped->m_player_info) {
								player.m_is_aiming = global::vars::g_ped_factory->m_local_ped->m_player_info->is_free_aiming();
							}
						}
					}
				} else {
					if (player.m_net_player) {
						if (player.m_net_player->m_player_info) {
							player.m_is_aiming = player.m_net_player->m_player_info->is_free_aiming();
						}
					}
				}

				native::get_current_ped_weapon(player.m_ped, &player.m_weapon_hash, false);

				native::network_handle_from_player(i, &player.m_network_handle.m_handle, (sizeof(player.m_network_handle) / 4));
				if (native::network_is_handle_valid(&player.m_network_handle.m_handle, (sizeof(player.m_network_handle) / 4))) {
					player.m_is_friend = native::network_is_friend(&player.m_network_handle.m_handle);
				}

				player.m_model = native::get_entity_model(player.m_ped);
				player.m_ped_headshot = script_global(1391551).at(player.m_id, 5).at(2).as<int>(); // 1.55 done
				player.m_vehicle = native::get_vehicle_ped_is_in(player.m_ped, false);
				player.m_alive = !native::is_entity_dead(player.m_ped, 0);
				player.m_heading = native::get_entity_heading(player.m_ped);
				player.m_coords = native::get_entity_coords(player.m_ped, true);
				player.m_in_vehicle = native::is_ped_in_any_vehicle(player.m_ped, true);
				player.m_has_weapon_in_hand = (player.m_weapon_hash && player.m_weapon_hash != 2725352035);
				player.m_rotation = native::get_entity_rotation(player.m_ped, 2);
				player.m_weapon_entity = native::get_current_ped_weapon_entity_index(player.m_ped);
				player.m_is_modder = std::count_if(begin(player.m_modder_flags), end(player.m_modder_flags), [](std::pair<ePlayerReportReasons, bool> element) { return element.second; }) > 0;

				if (player.m_in_vehicle) {
					player.m_entity = player.m_vehicle;
				} else {
					player.m_entity = player.m_ped;
				}

				if (player.m_connected) {
					if (i != native::player_id()) {
						if (player.m_model != 0x0 && player.m_model != 0x9c9effd8 && player.m_model != 0x705e61f2) {
							if (!player.m_modder_flags[menu::player::REASON_INVALID_MODEL]) {
								protection::reactions::vars::process_event(protection::reactions::vars::EVENT_INVALID_MODEL, player.m_id);

								menu::helpers::flag_modder(player.m_id, menu::player::REASON_INVALID_MODEL);
								menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_is_modding), TRANSLATE(t_invalid_model)), global::ui::g_error);
							}
						}

						if (player.m_name.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.") != std::string::npos || player.m_name.length() < 6) {
							if (!player.m_modder_flags[menu::player::REASON_SPOOFED_NAME]) {
								protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SPOOFED_NAME, player.m_id);

								menu::helpers::flag_modder(player.m_id, menu::player::REASON_SPOOFED_NAME);
								menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_is_modding), TRANSLATE(t_spoofed_name)), global::ui::g_error);
							}
						}

						if (menu::helpers::is_valid_net_player(player.m_net_player)) {
							player.m_rockstar_developer = player.m_net_player->m_is_rockstar_developer;

							if (((player.m_net_player->m_player_info->m_host_token >> 32) & 0xFFFFFFFF) < 0x1000 || player.m_net_player->m_player_info->m_host_token < 0x1000) {
								if (!player.m_modder_flags[menu::player::REASON_SPOOFED_PEER]) {
									protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SPOOFED_HOST_TOKEN, player.m_id);

									menu::helpers::flag_modder(player.m_id, menu::player::REASON_SPOOFED_PEER);
									menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_is_modding), TRANSLATE(t_spoofed_peer)), global::ui::g_error);
								}
							}

							auto relay_vit = std::find_if(begin(global::vars::g_relay_usage), end(global::vars::g_relay_usage), [=] (relay_usage& usage) {
								return !strcmp(usage.m_name, player.m_name.c_str()) && (usage.m_rockstar_id == player.m_net_player->m_player_info->m_rockstar_id || usage.m_rockstar_id == player.m_net_player->m_player_info->m_identifier.m_rockstar_id);
							});

							if (relay_vit != end(global::vars::g_relay_usage)) {
								if (player.m_net_player->m_player_info->m_external_ip != relay_vit->m_external_ip) {
									if (!player.m_modder_flags[menu::player::REASON_SPOOFED_IP]) {
										protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SPOOFED_IP, player.m_id);

										char buffer[32];
										sprintf(buffer, "%i.%i.%i.%i", ((relay_vit->m_external_ip & 0xFF000000) >> 24), ((relay_vit->m_external_ip & 0xFF0000) >> 16), ((relay_vit->m_external_ip & 0xFF00) >> 8), (relay_vit->m_external_ip & 0xFF));

										char spoofed_buffer[32];
										sprintf(spoofed_buffer, "%i.%i.%i.%i", ((player.m_net_player->m_player_info->m_external_ip & 0xFF000000) >> 24), ((player.m_net_player->m_player_info->m_external_ip & 0xFF0000) >> 16), ((player.m_net_player->m_player_info->m_external_ip & 0xFF00) >> 8), (player.m_net_player->m_player_info->m_external_ip & 0xFF));

										menu::helpers::flag_modder(player.m_id, menu::player::REASON_SPOOFED_IP);
										network::recents::vars::save(menu::helpers::clean_name(player.m_name), buffer, player.m_net_player->m_player_info->m_identifier.m_rockstar_id);
										menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s, %s %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_is_spoofing_ip), spoofed_buffer, TRANSLATE(t_is_spoofing_ip_real), buffer), global::ui::g_error);
									}

									player.m_net_player->m_player_info->m_external_ip = relay_vit->m_external_ip;
								}
							}

							static std::pair<int, std::pair<menu::player::ePlayerReportReasons, localization*>> frame_flags[] = {
								{ 0x800, { menu::player::REASON_EXPLOSIVE_AMMO, &(t_explosive_ammo) } },
								{ 0x2000, { menu::player::REASON_EXPLOSIVE_MELEE, &(t_explosive_melee) } },
								{ 0x1000, { menu::player::REASON_FIRE_AMMO, &(t_fire_ammo) } },
								{ 0x4000, { menu::player::REASON_SUPER_JUMP, &(t_super_jump) } }
							};

							for (std::pair<int, std::pair<menu::player::ePlayerReportReasons, localization*>>& flag : frame_flags) {
								if ((player.m_net_player->m_player_info->m_frame_flags & flag.first) != 0) {
									if (!player.m_modder_flags[flag.second.first]) {
										if (flag.first == 0x4000) {
											protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SUPER_JUMP, player.m_id);
										}

										menu::helpers::flag_modder(player.m_id, flag.second.first);
										menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_is_modding), flag.second.second->get().c_str()), global::ui::g_error);
									}
								}
							}

							if (player.m_net_player->m_player_info->m_rockstar_id < 10000
								|| player.m_net_player->m_player_info->m_identifier.m_rockstar_id < 10000
								|| player.m_net_player->m_player_info->m_identifier.m_rockstar_id != player.m_net_player->m_player_info->m_rockstar_id) {
								if (!player.m_modder_flags[menu::player::REASON_SPOOFED_RID]) {
									protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SPOOFED_RID, player.m_id);

									menu::helpers::flag_modder(player.m_id, menu::player::REASON_SPOOFED_RID);
									menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_is_modding), TRANSLATE(t_spoofed_rid)), global::ui::g_error);
								}
							}

							static std::pair<std::pair<int, menu::player::ePlayerReportReasons>, localization*> reasons[] = {
								{ { 0, REASON_CRC_FLOOD }, &(t_crc_flood) },
								{ { 1, REASON_CRC_COMPROMISED }, &(t_crc_compromised) },
								{ { 2, REASON_CRC_NOT_REPLIED }, &(t_crc_not_replied) },
								{ { 4, REASON_INFO_CHANGE_1 }, &(t_info_change1) },
								{ { 7, REASON_INFO_CHANGE_4 }, &(t_info_change4) },
								{ { 8, REASON_INFO_CHANGE_5 }, &(t_info_change5) },
								{ { 9, REASON_INFO_CHANGE_6 }, &(t_info_change6) },
								{ { 10, REASON_INFO_CHANGE_7 }, &(t_info_change7) }
							};

							for (std::pair<std::pair<int, menu::player::ePlayerReportReasons>, localization*>& reason : reasons) {
								for (int i = 0; i < 10; i++) {
									if (rage::engine::is_player_reported(player.m_net_player, reason.first.first, i)) {
										if (!player.m_modder_flags[reason.first.second]) {
											if (reason.first.first > 2) {
												protection::reactions::vars::process_event(protection::reactions::vars::EVENT_INFO_CHANGE, player.m_id);
											}

											menu::helpers::flag_modder(player.m_id, reason.first.second);
											menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_got_reported), reason.second->get().c_str()), global::ui::g_error);
										}

										break;
									}
								}
							}

							if (rage::engine::is_player_reported(player.m_net_player, 5, 0)) {
								if (!player.m_modder_flags[menu::player::REASON_INFO_CHANGE_2]) {
									protection::reactions::vars::process_event(protection::reactions::vars::EVENT_INFO_CHANGE, player.m_id);

									menu::helpers::flag_modder(player.m_id, menu::player::REASON_INFO_CHANGE_2);
									menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_got_reported), TRANSLATE(t_info_change2)), global::ui::g_error);
								}
							}

							if (rage::engine::is_player_reported(player.m_net_player, 6, 0)) {
								if (!player.m_modder_flags[menu::player::REASON_ARXAN]) {
									protection::reactions::vars::process_event(protection::reactions::vars::EVENT_ARXAN, player.m_id);

									menu::helpers::flag_modder(player.m_id, menu::player::REASON_ARXAN);
									menu::notify::stacked(TRANSLATE(t_modder_detection), util::va::va("%s %s: %s", menu::helpers::clean_name(player.m_name).c_str(), TRANSLATE(t_got_reported), TRANSLATE(t_arxan)), global::ui::g_error);
								}
							}
						}
					}
				}
			}
		}
	}

	void player_manager::for_each(std::function<void(player_context&)> callback, bool bypass_excludes, bool bypass_ghost) {
		for (player_context& player : m_players) {
			if (!bypass_ghost) {
				if (!player.m_exists) continue;
			}

			if (player.m_connected) {
				if (!bypass_excludes) {
					if (is_excluded(player.m_id)) continue;
				}

				callback(player);
			}
		}
	}

	player_context& player_manager::get_player(int index) {
		if (index < 0 || index> 32) {
			static player_context nigger;
			memset(&nigger, 0, sizeof(nigger));
			return nigger;
		}

		return m_players[index];
	}

	player_context& player_manager::get_local_player() {
		return m_players[native::player_id()];
	}

	player_context& player_manager::get_selected_player() {
		return m_players[network::players::vars::m_vars.m_selected_player];
	}

	bool player_manager::is_excluded(Player id) {
		return (network::session::excludes::vars::m_vars.m_self && id == get_local_player().m_id)
			|| (network::session::excludes::vars::m_vars.m_friends && get_player(id).m_is_friend)
			|| (network::session::excludes::vars::m_vars.m_host && get_player(id).m_net_player == rage::engine::get_host_net_game_player())
			|| (network::session::excludes::vars::m_vars.m_modders && get_player(id).m_is_modder)
			|| (network::session::excludes::vars::m_vars.m_rockstar_developers && get_player(id).m_rockstar_developer)
			|| (network::session::excludes::vars::m_vars.m_script_host && get_player(id).m_is_script_host);
	}

	player_context& player_manager::random(int ignore_index) {
	start:
		std::random_device r;
		std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
		std::mt19937 rng(seed2);
		std::uniform_int_distribution<int> val(0, 31);

		int index = val(rng);

		if (!m_players[index].m_connected || index == ignore_index) {
			goto start;
		}

		return m_players[index];
	}

	player_manager* get_player_manager() {
		static player_manager instance;
		return &instance;
	}

	std::string get_report_reason(ePlayerReportReasons reason) {
		switch (reason) {
			case REASON_INVALID_MODEL: return TRANSLATE(t_invalid_model);
			case REASON_SPOOFED_NAME: return TRANSLATE(t_spoofed_name);
			case REASON_SPOOFED_PEER: return TRANSLATE(t_spoofed_peer);
			case REASON_SPOOFED_RID: return TRANSLATE(t_spoofed_rid);
			case REASON_SPOOFED_IP: return TRANSLATE(t_spoofed_ip);
			case REASON_CRC_FLOOD: return TRANSLATE(t_crc_flood);
			case REASON_CRC_COMPROMISED: return TRANSLATE(t_crc_compromised);
			case REASON_CRC_NOT_REPLIED: return TRANSLATE(t_crc_not_replied);
			case REASON_INFO_CHANGE_1: return TRANSLATE(t_info_change1);
			case REASON_INFO_CHANGE_2: return TRANSLATE(t_info_change2);
			case REASON_INFO_CHANGE_4: return TRANSLATE(t_info_change4);
			case REASON_INFO_CHANGE_5: return TRANSLATE(t_info_change5);
			case REASON_INFO_CHANGE_6: return TRANSLATE(t_info_change6);
			case REASON_INFO_CHANGE_7: return TRANSLATE(t_info_change7);
			case REASON_ARXAN: return TRANSLATE(t_arxan);
			case REASON_SPOOFED_CHAT: return TRANSLATE(t_spoofed_chat);
			case REASON_SPOOFED_TEXT: return TRANSLATE(t_spoofed_text);
			case REASON_CRASH_ATTEMPT: return TRANSLATE(t_crash_attempt);
			case REASON_WEATHER_CHANGE: return TRANSLATE(t_weather_change);
			case REASON_SPECTATING: return TRANSLATE(t_spectating);
			case REASON_EXPLOSIVE_AMMO: return TRANSLATE(t_explosive_ammo);
			case REASON_EXPLOSIVE_MELEE: return TRANSLATE(t_explosive_melee);
			case REASON_FIRE_AMMO: return TRANSLATE(t_fire_ammo);
			case REASON_SUPER_JUMP: return TRANSLATE(t_super_jump);
			case REASON_MONEY_DROP: return TRANSLATE(t_money_drop);
			case REASON_RP_DROP: return TRANSLATE(t_rp_drop);
			case REASON_QUANTUM_KICK: return TRANSLATE(t_quantum_kick);
			case REASON_SCRIPT_MIGRATION: return TRANSLATE(t_script_migration);
			case REASON_PROFANITY: return TRANSLATE(t_profanity);
			case REASON_JOIN_TIMEOUT: return TRANSLATE(t_join_timeout);
			case REASON_INFO_MISMATCH: return TRANSLATE(t_info_mismatch);
			/*case REASON_MENU_CHERAX: return TRANSLATE(t_cherax);
			case REASON_MENU_IMPULSE: return TRANSLATE(t_impulse);
			case REASON_MENU_IMPULSE_VIP: return TRANSLATE(t_impulse_vip);
			case REASON_MENU_IMPULSE_STAFF: return TRANSLATE(t_impulse_staff);
			case REASON_MENU_IMPULSE_BLOCK: return TRANSLATE(t_impulse_block);*/
			case REASON_GHOST: return TRANSLATE(t_ghost_player);
		}

		return "None";
	}
}