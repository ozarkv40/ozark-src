#include "network_players_friendly_drops.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_friendly.h"
#include "global/lists.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/control.h"

using namespace network::players::friendly::drops::vars;

namespace network::players::friendly::drops::vars {
	variables m_vars;

	scroll_struct<uint32_t> drop_type[] = {
		{ localization("Money", true), 0xE175C698 },
		{ localization("RP", true), 0x2C014CA6 },
	};

	scroll_struct<uint32_t> drop_models[] = {
		{ localization("Money Bag", true), 0x113FD533 },
		{ localization("Alien Egg", true), 0x6B795EBC },
		{ localization("Weed", true), 0x1AFA6A0A },
		{ localization("Beach Fire", true), 0xC079B265 },
		{ localization("Xmas Tree", true), 0xE3BA450 },
		{ localization("Bear", true), 0x772114C9 },
		{ localization("Gold Bar", true), 0xF046EA37 },
		{ localization("Guitar", true), 0xA4E7E0A7 },
		{ localization("Dildo", true), 0xE6CB661E },
		{ localization("Basketball", true), 0x6DB9599A },
		{ localization("Bong", true), 0xF0A61994 },
		{ localization("C4", true), 0xB4861EB7 },
		{ localization("Ammo Box", true), 0x6DE6824F },
		{ localization("Toilet", true), 0x6F9939C7 },
		{ localization("Wheelchair", true), 0x4B3D240F }
	};

	scroll_struct<int> drop_styles[] = {
		{ localization("Traditional", true), 0 },
		{ localization("Rain", true), 0 },
		{ localization("Shower", true), 0 },
		{ localization("Bait", true), 0 }
	};

	scroll_struct<uint32_t> drop_pickups[] = {
		{ localization("Armor", true), 0x4BFB42D1 },
		{ localization("Health Pack", true), 0x8F707C18 },
		{ localization("Repair Kit", true), 0x098D79EF }
	};

	scroll_struct<uint32_t> drop_weapons[] = {
		{ localization("RPG", true), 0x4D36C349 },
		{ localization("Minigun", true), 0x2F36B434 },
		{ localization("Parachute", true), 0x6773257D },
		{ localization("Fire Extinguisher", true), 0xCB13D282 },
		{ localization("Flare", true), 0xE013E01C },
		{ localization("Flare Gun", true), 0xBD4DE242 },
		{ localization("Crowbar", true), 0x872DC888 },
		{ localization("Firework", true), 0x22B15640 },
	};

	void spawn_drop(menu::player::player_context& player, uint32_t model) {
		native::create_ambient_pickup(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, 1, 0, false, true);
	}
}

void network_players_friendly_drops_menu::load() {
	set_name("Drops");
	set_parent<network_players_friendly_menu>();

	add_option(scroll_option<uint32_t>(TOGGLE, "Drop Type")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_drop_toggle)
		.add_scroll(menu::player::get_selected_player().m_drop_type, 0, NUMOF(drop_type), drop_type)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_drop_toggle);
				option->add_scroll(menu::player::get_selected_player().m_drop_type, 0, NUMOF(drop_type), drop_type);
			} else {
				option->add_toggle(m_vars.m_drop_toggle);
				option->add_scroll(m_vars.m_drop_type, 0, NUMOF(drop_type), drop_type);
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Drop Pickup")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_drop_pickup, 0, NUMOF(drop_pickups), drop_pickups)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_drop_pickup, 0, NUMOF(drop_pickups), drop_pickups);
			} else {
				option->add_scroll(m_vars.m_drop_pickup, 0, NUMOF(drop_pickups), drop_pickups);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				spawn_drop(menu::player::get_selected_player(), drop_pickups[menu::player::get_selected_player().m_drop_pickup].m_result);
			} else {
				spawn_drop(menu::player::get_selected_player(), drop_pickups[m_vars.m_drop_pickup].m_result);
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Drop Weapon")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_drop_weapon, 0, NUMOF(drop_weapons), drop_weapons)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_drop_weapon, 0, NUMOF(drop_weapons), drop_weapons);
			} else {
				option->add_scroll(m_vars.m_drop_weapon, 0, NUMOF(drop_weapons), drop_weapons);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				spawn_drop(menu::player::get_selected_player(), drop_weapons[menu::player::get_selected_player().m_drop_weapon].m_result);
			} else {
				spawn_drop(menu::player::get_selected_player(), drop_weapons[m_vars.m_drop_weapon].m_result);
			}
		}));

	add_option(break_option("Settings")
		.add_translate());

	add_option(toggle_option("Stealth")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_drop_stealth)
		.add_tooltip("The pickup will only be synced to this player")
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));

	add_option(scroll_option<int>(SCROLL, "Style")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_drop_money_style, 0, NUMOF(drop_styles), drop_styles)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_drop_money_style, 0, NUMOF(drop_styles), drop_styles);
			} else {
				option->add_scroll(m_vars.m_drop_money_style, 0, NUMOF(drop_styles), drop_styles);
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLL, "Delay")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_drop_money_delay, 0, NUMOF(global::lists::g_timers), global::lists::g_timers)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_drop_money_delay, 0, NUMOF(global::lists::g_timers), global::lists::g_timers);
			} else {
				option->add_scroll(m_vars.m_drop_money_delay, 0, NUMOF(global::lists::g_timers), global::lists::g_timers);
			}
		})
		.add_tooltip("Leave on 2.5s delay for money drop to prevent error messages"));
}

void network_players_friendly_drops_menu::update() {}

void network_players_friendly_drops_menu::update_once() {}

void network_players_friendly_drops_menu::feature_update() {
	menu::player::for_each([] (menu::player::player_context& player) {
		if (player.m_drop_toggle) {
			math::vector3<float> coords;
			switch (player.m_drop_money_style) {
				case 0: coords = player.m_coords; break;
				case 1: coords = native::get_offset_from_entity_in_world_coords(player.m_ped, native::get_random_float_in_range(-3.f, 3.f), native::get_random_float_in_range(-3.f, 3.f), native::get_random_float_in_range(-3.f, 3.f)); break;
				case 2: coords = native::get_offset_from_entity_in_world_coords(player.m_ped, 0.f, 0.f, 2.f); break;
				case 3: coords = native::get_offset_from_entity_in_world_coords(player.m_ped, 0.f, 2.f, 0.f); break;
			}

			menu::timers::run_timed(&player.m_drop_money_timer, global::lists::g_timers[player.m_drop_money_delay].m_result, [=] {
				uint32_t model = player.m_drop_type == 0 ? drop_models[player.m_drop_money_model].m_result : joaat("vw_prop_vw_colle_alien");
				menu::control::request_model(model, [=] (uint32_t M) {
					native::create_ambient_pickup(drop_type[player.m_drop_type].m_result, coords.x, coords.y, coords.z, 0, player.m_drop_type == 0 ? 2000 : 10, M, false, true);
				});
			});
		}
	}, true);

	if (m_vars.m_drop_toggle) {
		menu::timers::run_timed(&m_vars.m_drop_money_timer, global::lists::g_timers[m_vars.m_drop_money_delay].m_result, [=] {
			menu::player::for_each([] (menu::player::player_context& player) {
				if (player.m_drop_toggle) return;

				math::vector3<float> coords;
				switch (m_vars.m_drop_money_style) {
					case 0: coords = player.m_coords; break;
					case 1: coords = native::get_offset_from_entity_in_world_coords(player.m_ped, native::get_random_float_in_range(-3.f, 3.f), native::get_random_float_in_range(-3.f, 3.f), native::get_random_float_in_range(-3.f, 3.f)); break;
					case 2: coords = native::get_offset_from_entity_in_world_coords(player.m_ped, 0.f, 0.f, 2.f); break;
					case 3: coords = native::get_offset_from_entity_in_world_coords(player.m_ped, 0.f, 2.f, 0.f); break;
				}

				uint32_t model = m_vars.m_drop_type == 0 ? drop_models[m_vars.m_drop_money_model].m_result : joaat("vw_prop_vw_colle_alien");
				menu::control::request_model(model, [=] (uint32_t M) {
					native::create_ambient_pickup(drop_type[m_vars.m_drop_type].m_result, coords.x, coords.y, coords.z, 0, m_vars.m_drop_type == 0 ? 2500 : 10, M, false, true);
				});
			});
		});
	}
}

network_players_friendly_drops_menu* g_instance;
network_players_friendly_drops_menu* network_players_friendly_drops_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_friendly_drops_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}