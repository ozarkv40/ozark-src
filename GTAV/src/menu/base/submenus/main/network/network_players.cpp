#include "network_players.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "menu/base/util/panels.h"
#include "menu/base/util/timers.h"
#include "rage/engine.h"
#include "menu/base/util/helpers.h"
#include "menu/base/util/global.h"
#include "players/network_players_selected.h"
#include "menu/base/submenus/main/settings/hide_info.h"
#include "rage/types/global_types.h"

using namespace network::players::vars;

namespace network::players::vars {
	variables m_vars;

	scroll_struct<int> sort_types[] = {
		{ localization("Player ID", true), 0 },
		{ localization("Distance", true), 0 },
		{ localization("Alphabetical", true), 0 },
		{ localization("Bank Balance", true), 0 },
		{ localization("Wallet Balance", true), 0 },
		{ localization("Rank", true), 0 },
		{ localization("Modders", true), 0 },
		{ localization("Next Session Hosts", true), 0 },
	};

	std::string calculate_flags(menu::player::player_context& player) {
		network_players_menu* _this = network_players_menu::get();
		std::string _return = "";

		if (menu::helpers::is_valid_net_player(player.m_net_player)) {
			if (player.m_net_player == rage::engine::get_host_net_game_player()) {
				_return += "~HUD_COLOUR_BLUELIGHT~" + _this->get_string("[H]");
			}
		}

		/*if (player.m_modder_flags[menu::player::REASON_MENU_CHERAX]) {
			_return += _this->get_string("[CHERAX]");
		}

		if (player.m_modder_flags[menu::player::REASON_MENU_IMPULSE]
			&& !player.m_modder_flags[menu::player::REASON_MENU_IMPULSE_VIP]) {
			_return += _this->get_string("[IMP]");
		}

		if (player.m_modder_flags[menu::player::REASON_MENU_IMPULSE_VIP]) {
			_return += _this->get_string("[IMP-VIP]");
		}

		if (player.m_modder_flags[menu::player::REASON_MENU_IMPULSE_STAFF]) {
			_return += _this->get_string("[IMP-STAFF]");
		}

		if (player.m_modder_flags[menu::player::REASON_MENU_IMPULSE_BLOCK]) {
			_return += _this->get_string("[IMP-BLOCK]");
		}*/

		if (player.m_modder_flags[menu::player::REASON_GHOST]) {
			_return += _this->get_string("[GHOST]");
		}

		if (player.m_spectate) {
			_return += "~HUD_COLOUR_GREYLIGHT~" + _this->get_string("[SPEC]");
		}

		if (player.m_is_friend) {
			_return += "~HUD_COLOUR_BLUE~" + _this->get_string("[F]");
		}

		if (player.m_is_modder) {
			_return += "~g~" + _this->get_string("[M]");
		}

		if (player.m_is_script_host) {
			_return += "~o~" + _this->get_string("[SC-H]");
		}

		if (player.m_id > 31) {
			_return += "~r~" + _this->get_string("[SCTV]");
		}

		if (player.m_id == menu::player::get_local_player().m_id) {
			_return += "~HUD_COLOUR_PINK~" + _this->get_string("[ME]");
		}

		if (menu::helpers::is_valid_net_player(player.m_net_player)) {
			if (strlen(player.m_net_player->get_crew_name()) > 0) {
				std::string name = player.m_net_player->get_crew_tag();
				std::transform(name.begin(), name.end(), name.begin(), ::toupper);
				_return += "~HUD_COLOUR_BRONZE~[" + name + "]";
			}
		}

		return _return;
	}

	void render_sprite(menu::player::player_context& player, int pos) {
		auto render_base_icon = [](const char* name, int pos) {
			menu::renderer::draw_sprite({ "mpinventory", name },
				{ global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.012f },
				{ 0.017f * 0.8f, 0.027f * 0.8f }, 0.f, global::ui::g_option);
		};

		if (menu::helpers::is_valid_net_player(player.m_net_player)) {
			if (player.m_net_player->m_is_rockstar_developer || player.m_net_player->m_is_rockstar_qa) {
				return render_base_icon("custom_mission", pos);
			}
		}

		Blip blip_handle = menu::script_global(rage::global::_155_get_player_blip_handle + player.m_id + 1).as<Blip>();
		if (blip_handle == 0) blip_handle = native::get_blip_from_entity(player.m_ped);

		if (blip_handle) {
			int blip_id = native::get_blip_sprite(blip_handle);

			if (blip_id > 0 && blip_id != 164) {
				char blip_name[32];
				sprintf(blip_name, "blip_%i", blip_id);

				static const rage::types::grc_texture_dx11* invalid_sprite = rage::engine::get_sprite_texture("yes", "yes");
				rage::types::grc_texture_dx11* ozark_blip_sprite = rage::engine::get_sprite_texture("OzarkBlips", blip_name);

				if (ozark_blip_sprite && ozark_blip_sprite != invalid_sprite) {
					struct special {
						math::vector3_<float> m_coords;
						int m_sprite;
					};

					std::unordered_map<int, special> special_blips;
					float rotation = 0.f;

					for (int i = 0; i < 1500; i++) {
						rage::types::blip* blip = global::vars::g_blip_list->m_blips[i];
						if (blip) {
							if (blip->m_handle == blip_handle) {
								if (blip_id == 422) {
									blip->m_rotation += 5.f;
									if (blip->m_rotation == 360.f) blip->m_rotation = 0.f;
								}

								rotation = blip->m_rotation;
							}

							if (blip->m_sprite == 72
								|| blip->m_sprite == 71
								|| blip->m_sprite == 73
								|| blip->m_sprite == 75
								|| blip->m_sprite == 110) {
								special_blips[blip->m_handle] = { blip->m_coords, blip->m_sprite };
							}
						}
					}

					uint32_t blip_color_hex = (uint32_t)native::get_blip_colour(blip_handle);
					color_rgba blip_color = color_rgba(blip_color_hex);
					if (blip_color_hex < 500) {
						blip_color = menu::helpers::get_color_from_blip(blip_color_hex);
					}

					if (!native::is_player_control_on(player.m_id)) {
						for (std::pair<int, special> special_blip : special_blips) {
							if (math::vector3_<float>::to_padded(special_blip.second.m_coords).get_distance(native::get_blip_coords(blip_handle)) < 18.f) {
								sprintf(blip_name, "blip_%i", special_blip.second.m_sprite);
								blip_color = { 255, 255, 255 };
								rotation = 0.f;
								break;
							}
						}
					}

					menu::renderer::draw_sprite({ "OzarkBlips", blip_name },
						{ global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.012f },
						{ 0.017f * 0.8f, 0.027f * 0.8f }, rotation, blip_color);

					return;
				}
			}
		}

		if (!player.m_in_vehicle) {
			menu::renderer::draw_sprite({ "OzarkBlips", "blip_1" },
				{ global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.012f },
				{ 0.017f * 0.8f, 0.027f * 0.8f }, 0.f, { 255, 255, 255, 255 });

			return;
		}

		// menu::base::is_option_selected(pos)

		uint32_t vehicle_model = native::get_entity_model(player.m_vehicle);
		if (native::is_this_model_a_bicycle(vehicle_model)) {
			return render_base_icon(false ? "mp_specitem_bike_black" : "mp_specitem_bike", pos);
		}

		if (native::is_this_model_a_bike(vehicle_model)) {
			return render_base_icon(false ? "mp_specitem_bike_black" : "mp_specitem_bike", pos);
		}

		if (native::is_this_model_a_boat(vehicle_model)) {
			return render_base_icon(false ? "mp_specitem_boat_black" : "mp_specitem_boat", pos);
		}

		if (native::is_this_model_a_heli(vehicle_model)) {
			return render_base_icon(false ? "mp_specitem_heli_black" : "mp_specitem_heli", pos);
		}

		if (native::is_this_model_a_plane(vehicle_model)) {
			return render_base_icon(false ? "mp_specitem_plane_black" : "mp_specitem_plane", pos);
		}

		return render_base_icon(false ? "mp_specitem_car_black" : "mp_specitem_car", pos);
	}
}

void network_players_menu::load() {
	set_name("Players");
	set_parent<network_menu>();

	add_option(scroll_option<int>(SCROLL, "Sort Players")
		.add_translate()
		.add_scroll(m_vars.m_sort, 0, NUMOF(sort_types), sort_types));

	add_option(break_option("Players")
		.add_translate());

	add_string("[H]");
	add_string("[CHERAX]");
	add_string("[IMP]");
	add_string("[IMP-VIP]");
	add_string("[IMP-STAFF]");
	add_string("[IMP-BLOCK]");
	add_string("[GHOST]");
	add_string("[SPEC]");
	add_string("[F]");
	add_string("[M]");
	add_string("[SC-H]");
	add_string("[SCTV]");
	add_string("[ME]");

	network_players_selected_menu::get();
}

void network_players_menu::update() {
	static int timer = 0;
	menu::timers::run_timed(&timer, 250, [this] {
		clear_options(2);

		std::vector<menu::player::player_context*> players;
		menu::player::for_each([&](menu::player::player_context& player) {
			if (!player.m_name.empty()) {
				players.push_back(&player);
			}
		}, true, true);

		if (m_vars.m_sort != 0) {
			switch (m_vars.m_sort) {
				case 1:
					std::sort(begin(players), end(players), [](menu::player::player_context* left, menu::player::player_context* right) {
						return left->m_coords.get_distance(menu::player::get_local_player().m_coords) < right->m_coords.get_distance(menu::player::get_local_player().m_coords);
					});
					break;

				case 2:
					std::sort(begin(players), end(players), [](menu::player::player_context* left, menu::player::player_context* right) {
						int i = 0;
						std::string name1 = left->m_name;
						std::string name2 = right->m_name;

						while ((i < name1.length()) && (i < name2.length())) {
							if (tolower(name1[i]) < tolower(name2[i])) return true;
							if (tolower(name1[i]) > tolower(name2[i])) return false;
							i++;
						}

						return name1.length() < name2.length();
					});
					break;

				case 3:
					std::sort(begin(players), end(players), [](menu::player::player_context* left, menu::player::player_context* right) {
						int left_bank = menu::script_global(rage::global::_155_player_stats_struct).at(left->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(56).as<int>() - menu::script_global(rage::global::_155_player_stats_struct).at(left->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>();
						int right_bank = menu::script_global(rage::global::_155_player_stats_struct).at(right->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(56).as<int>() - menu::script_global(rage::global::_155_player_stats_struct).at(right->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>();
						return left_bank > right_bank;
					});
					break;

				case 4:
					std::sort(begin(players), end(players), [](menu::player::player_context* left, menu::player::player_context* right) {
						int left_wallet = menu::script_global(rage::global::_155_player_stats_struct).at(left->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>();
						int right_wallet = menu::script_global(rage::global::_155_player_stats_struct).at(right->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>();
						return left_wallet > right_wallet;
					});
					break;

				case 5:
					std::sort(begin(players), end(players), [](menu::player::player_context* left, menu::player::player_context* right) {
						int left_rank = menu::script_global(rage::global::_155_player_stats_struct).at(left->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(6).as<int>();
						int right_rank = menu::script_global(rage::global::_155_player_stats_struct).at(right->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(6).as<int>();
						return left_rank > right_rank;
					});
					break;

				case 6:
					std::sort(begin(players), end(players), [](menu::player::player_context* left, menu::player::player_context* right) {
						return left->m_is_modder;
					});
					break;

				case 7:
					std::sort(begin(players), end(players), [](menu::player::player_context* left, menu::player::player_context* right) {
						if (rage::engine::get_host_net_game_player() == left->m_net_player) return false;

						uint64_t left_token = 0;
						uint64_t right_token = 0;

						if (is_valid_ptr(left->m_net_player)) {
							if (is_valid_ptr(left->m_net_player->m_player_info)) {
								left_token = left->m_net_player->m_player_info->m_host_token;
							}
						}

						if (is_valid_ptr(right->m_net_player)) {
							if (is_valid_ptr(right->m_net_player->m_player_info)) {
								right_token = right->m_net_player->m_player_info->m_host_token;
							}
						}

						return left_token < right_token;
					});
					break;
			}
		}

		for (menu::player::player_context* player : players) {
			std::string name = menu::helpers::clean_name(player->m_name);
			if (player->m_id == menu::player::get_local_player().m_id) {
				if (settings::hide::vars::m_vars.m_hide_names) {
					name = util::va::va("Player_%i", player->m_id);
				}
			}

			switch (m_vars.m_sort) {
				case 1: name = "[" + std::string(util::va::va("%.3f", player->m_coords.get_distance(menu::player::get_local_player().m_coords))) + "m] " + name; break;
				case 3: name = "[$" + std::to_string(menu::script_global(rage::global::_155_player_stats_struct).at(player->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(56).as<int>() - menu::script_global(rage::global::_155_player_stats_struct).at(player->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>()) + "] " + name; break;
				case 4: name = "[$" + std::to_string(menu::script_global(rage::global::_155_player_stats_struct).at(player->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(3).as<int>()) + "] " + name; break;
				case 5: name = "[" + std::to_string(menu::script_global(rage::global::_155_player_stats_struct).at(player->m_id, rage::global::_155_player_stats_size).at(rage::global::_155_player_stats_start).at(6).as<int>()) + "] " + name; break;
			}

			add_option(submenu_option(name)
				.add_submenu<network_players_selected_menu>()
				.add_update([=](submenu_option* option, int pos) {
					option->add_offset(0.016f);
					render_sprite(*player, pos);
				}).add_hover([=](submenu_option* option) {
					m_vars.m_selected_player = player->m_id;

					menu::panels::panel_custom_screen_ped_preview preview;
					preview.m_screen_offset = { 0.00f, -2.00f, 0.40f };
					preview.m_is_player = true;
					preview.m_player = player->m_id;

					menu::panels::set_structure(menu::panels::get_child(menu::panels::get_parent("PANEL_PLAYER_INFO"), "PANEL_PLAYER_INFO_OUTFIT_PREVIEW"), (void*)&preview, sizeof(preview));
					menu::panels::toggle_panel_render("PANEL_PLAYER_INFO", true);
				}).add_click([=] {
					if (player->m_modder_flags[menu::player::REASON_GHOST]) {
						menu::submenu::handler::set_submenu(network_players_menu::get());
					}
				}).add_side_text(calculate_flags(*player)).disable_icon());
		}
	});

	if (menu::base::get_current_option() >= (int)get_options().size()) {
		menu::base::set_current_option((int)get_options().size() - 1);
	}

	if (menu::base::get_current_option() <= 1) {
		menu::panels::toggle_panel_render("PANEL_PLAYER_INFO", false);
	}
}

void network_players_menu::update_once() {}

void network_players_menu::feature_update() {
	menu::player::for_each([&] (menu::player::player_context& player) {
		if (!menu::player::get_local_player().m_alive) {
			if (player.m_spectate) {
				native::network_set_in_spectator_mode(false, player.m_ped);
			}
		}
	}, true, true);
}

network_players_menu* g_instance;
network_players_menu* network_players_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}